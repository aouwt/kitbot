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
#include <unistd.h>

#define	FMT_VA \
	char msg [512];	\
	va_list ap;	\
	va_start (ap, fmt);	\
	vsnprintf (msg, 512, fmt, ap);	\
	va_end (ap);

void IRC_Poll (IRC_Connection *conn) {
	size_t oldbufsz = conn->buf.bufend - conn->buf.buf;
	
	while (1) {
		size_t cursz = conn->buf.bufend - conn->buf.buf;
		if (conn->buf.bufend + 16 >= (conn->buf.alloc + conn->buf.buf)) {
			conn->buf.buf = realloc (conn->buf.buf, (conn->buf.alloc *= 2));
			conn->buf.bufend = conn->buf.buf + cursz;
			
		}
		
		ssize_t r = read (
			conn->sockfd,
			conn->buf.bufend,
			(sizeof (char) * (conn->buf.alloc - cursz)) - 2
		);
		
		if (r > 0)
			conn->buf.bufend += r;
		else
			break;
	}
	
	*conn->buf.bufend = '\0';
	if (conn->buf.bufend != oldbufsz + conn->buf.buf)
		printf (">%s", conn->buf.buf + oldbufsz);
}

IRC_Command *IRC_GetCommand (IRC_Connection *conn, IRC_Command *out) {
	IRC_Poll (conn);
	char *needle;
	
	if ((needle = strstr (conn->buf.buf, "\r\n")) == NULL)
		return NULL;
	
	*needle = '\0';
	
	out->from = conn;
	out->argc = 0;
	
	out->argv [out->argc ++] = conn->buf.buf;
	for (char *i = conn->buf.buf; *i != '\n'; i ++) {
		if (*i == ' ') {
			out->argv [out->argc] = i + 1;
			*i = '\0';
			
			if (*(i + 1) == ':') {
				*(out->argv [out->argc] ++) = '\0';
				break;
			}
			out->argc ++;
		}
	}
	
	if (strcmp (out->argv [0], "PING") == 0)
		IRC_SendCmdF (conn, "PONG :%s", out->argv [1] + 1);
	
	return out;
}

IRC_Message *IRC_GetMessage (IRC_Connection *conn, IRC_Message *out) {
	IRC_Command cmd;
	if (IRC_GetCommand (conn, &cmd) == NULL)
		return NULL;
	return IRC_GetPRIVMSG (&cmd, out);
}

IRC_Message *IRC_GetPRIVMSG (IRC_Command *cmd, IRC_Message *out) {
	if (strcmp (cmd->argv [1], "PRIVMSG") != 0)
		return NULL;
	
	strncpy (out->from.nick, cmd->argv [0], cmd->argv [0] - strchr (cmd->argv [0], '!'));
	strcpy (out->from.full, cmd->argv [0]);
	
	strcpy (out->ch.chan_name, cmd->argv [2]);
	out->ch.conn = cmd->from;
	
	strcpy (out->msg, cmd->argv [3]);
}

void sendmesg (IRC_Connection *conn, const char *msg) {
	size_t len = strlen (msg);
	size_t sent = 0;
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
	
	out->sockfd = -1;
	out->domain = strdup (domain);
	out->port = port;
	out->buf.buf = malloc (16 * sizeof (char));
	out->buf.bufend = out->buf.buf;
	out->buf.alloc = 16;
	
	return out;
}

void IRC_FreeConnection (IRC_Connection *conn) {
	free (conn->buf.buf);
	free (conn);
}

IRC_Connection *IRC_OpenConnection (IRC_Connection *conn) {
	//puts ("bees");
	struct addrinfo *ai;
	if (getaddrinfo (conn->domain, NULL, NULL, &ai))
		return NULL;
		
	//puts ("bees2");
	
	if (conn->sockfd == -1) {
		conn->sockfd = socket (ai->ai_family, ai->ai_socktype, ai->ai_protocol);
		
		if (conn->sockfd == -1)
			return NULL;
		
		if (fcntl (conn->sockfd, F_SETFL, O_NONBLOCK))
			return NULL;
		
		((struct sockaddr_in*) ai->ai_addr)->sin_port = htons (conn->port);
		
		bool cont = false;
		do {
			connect (conn->sockfd, ai->ai_addr, ai->ai_addrlen);
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
	
	freeaddrinfo (ai);
	
	return conn;
}

void IRC_CloseConnection (IRC_Connection *conn) {
	close (conn->sockfd);
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

void IRC_EndConnection (IRC_Connection *conn) {
	IRC_CloseConnection (conn);
	IRC_FreeConnection (conn);
}
