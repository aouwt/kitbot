#include "irc.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <errno.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#define	FMT_VA \
	char msg [512];	\
	va_list ap;	\
	va_start (ap, fmt);	\
	vsnprintf (msg, 512, fmt, ap);	\
	va_end (ap);

void IRC_Poll (IRC_Connection *conn) {
	ssize_t r = 0;
	while ((
		r = recv (
			conn->sockfd,
			conn->buf.bufend,
			(sizeof (char) * conn->buf.alloc) - (size_t) (conn->buf.bufend - conn->buf.buf),
			0
		)
	) > 0) {
		conn->buf.bufend += r;
		if (conn->buf.bufend == (conn->buf.alloc + conn->buf.buf)) {
			conn->buf.buf = realloc (conn->buf.buf, (conn->buf.alloc *= 2));
		}
	}
	
	*conn->buf.bufend = '\0';
	if (conn->buf.buf [0] != '\0')
		printf (">%s\n", conn->buf.buf);
}

IRC_Command *IRC_GetCommand (IRC_Connection *conn) {
	char *needle;
	if ((needle = strstr (conn->buf.buf, "\r\n")) == NULL)
		return NULL;
	
	*needle = '\0';
	
	IRC_Command *out = malloc (sizeof (IRC_Command));
	out->argc = 0;
	
	out->argv [out->argc ++] = conn->buf.buf;
	for (char *i = conn->buf.buf; *i != '\n'; i ++) {
		if (*i == ' ') {
			out->argv [out->argc ++] = i + 1;
			*i = '\0';
		
		} else
		if (*i == ':') {
			out->argv [out->argc ++] = i + 1;
			break;
		}
	}
	
}

void sendmesg (IRC_Connection *conn, const char *msg) {
	size_t len = strlen (msg);
	int sent = 0;
	int packet;
	
	IRC_Poll (conn);
	
	do {
		packet = send (conn->sockfd, msg + sent, len - sent, 0);
		
		if (packet >= 0)
			sent += packet;
	} while (sent < len);
	
	// send the \r\n
	const char rn [] = { '\r', '\n' };
	len = 2;
	sent = 0;
	do {
		packet = send (conn->sockfd, rn + sent, len - sent, 0);
		
		if (packet >= 0)
			sent += packet;
	} while (sent < len);
	printf ("<%s\n", msg);
}

void sendfmtmesg (IRC_Connection *conn, const char *fmt, ...)
	{	FMT_VA;	sendmesg (conn, msg);	}


void IRC_Send (IRC_Channel *chan, const char *msg)
	{	IRC_SendToCh (chan->conn, chan->chan_name, msg);	}
	
void IRC_SendF (IRC_Channel *chan, const char *fmt, ...)
	{	FMT_VA;	IRC_Send (chan, msg);	}


void IRC_SendToCh (IRC_Connection *conn, const char *chan, const char *msg)
	{	sendfmtmesg (conn, "PRIVMSG %s :%s", chan, msg);	}
	
void IRC_SendToChF (IRC_Connection *conn, const char *chan, const char *fmt, ...)
	{	FMT_VA;	IRC_SendToCh (conn, chan, msg);	}


void IRC_SendCmd (IRC_Connection *conn, const char *cmdline)
	{	sendmesg (conn, cmdline);	}
	
void IRC_SendCmdF (IRC_Connection *conn, const char *fmt, ...)
	{	FMT_VA;	sendmesg (conn, msg);	}
	

void IRC_JoinChannel (IRC_Channel *chan)
	{	IRC_SendCmdF (chan->conn, "JOIN %s", chan->chan_name);	}
	
void /*IRC_Channel **/IRC_JoinChannelByName (IRC_Connection *conn, const char *chan)
	{	IRC_SendCmdF (conn, "JOIN %s", chan);	}



IRC_Connection *IRC_AllocConnection (const char *domain, unsigned int port) {
	IRC_Connection *out = malloc (sizeof (IRC_Connection));
	
	if (port == 0)
		port = 6667;
	
	out->channels_avail = NULL;
	out->channels = NULL;
	out->sockfd = -1;
	out->domain = strdup (domain);
	out->port = port;
	out->addrinfo = NULL;
	out->motd = NULL;
	out->buf.buf = malloc (16 * sizeof (char));
	out->buf.bufend = out->buf.buf;
	out->buf.alloc = 16 * sizeof (char);
	
	return out;
}

IRC_Connection *IRC_OpenConnection (IRC_Connection *conn) {
	//puts ("bees");
	if (conn->addrinfo == NULL) {
		if (getaddrinfo (conn->domain, NULL, NULL, &conn->addrinfo))
			return NULL;
	}
	//puts ("bees2");
	
	if (conn->sockfd == -1) {
		conn->sockfd = socket (conn->addrinfo->ai_family, conn->addrinfo->ai_socktype, conn->addrinfo->ai_protocol);
		
		if (conn->sockfd == -1)
			return NULL;
		
		if (fcntl (conn->sockfd, F_SETFL, O_NONBLOCK))
			return NULL;
		
		((struct sockaddr_in*) conn->addrinfo->ai_addr)->sin_port = htons (conn->port);
		
		bool cont = false;
		do {
			connect (conn->sockfd, conn->addrinfo->ai_addr, conn->addrinfo->ai_addrlen);
			switch (errno) {
				case EINPROGRESS:
					cont = true;
				break;
				case EALREADY:
					cont = false;
				break;
				default:
					return NULL;
				break;
			}
		} while (cont);
	}
	//puts ("bees3");
	
	return conn;
}

IRC_Connection *IRC_SetupConnection (IRC_Connection *conn, const char *name) {
	sendfmtmesg (conn, "USER %s %s %s %s", name, name, conn->domain, name);
	return conn;
}

IRC_Connection *IRC_NewConnection (IRC_Connection *conn, const char *domain, unsigned int port, const char *name) {
	if (conn == NULL)
		conn = IRC_AllocConnection (domain, port);
	
	if (IRC_OpenConnection (conn) == NULL)
		return NULL;
	
	//puts ("bees4");
	IRC_SetupConnection (conn, name);
	//puts ("bees5");
	return conn;
}

void IRC_SetNick (IRC_Connection *conn, const char *nick) {
	sendfmtmesg (conn, "NICK %s", nick);
}
