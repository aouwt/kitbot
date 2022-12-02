struct _IRC_User_Modes {
	char *text;
	signed char i, s, w, o;
}

struct _IRC_User {
	char *nick;
	char *name;
	char *host;
	char *full;
	IRC_Channel_Modes mode;
};

struct _IRC_Channel_Modes {
	char *text;
	signed char o, s, p, n, m, i, t, l, b, v, k;
}

struct _IRC_Channel {
	char *chan_name;
	IRC_User *users [];
	IRC_Connection *conn;
	IRC_Channel_Modes mode;
}

struct _IRC_Connection {
	struct {
		char *channels_avail [];
		IRC_Channel channels [];

		bool init;
	} irc;

	struct {
		int fd;
		char *domain;
		unsigned short port;
		struct addrinfo addrinfo;
	} sock;

	IRC_User me;
};

#define	FMT_VA(msg)	\
	char msg [512];	\
	va_list ap;	\
	va_start (ap, fmt);	\
	vsnprintf (msg, 512, fmt, ap);	\
	va_end (ap, fmt);

void sendmsg (IRC_Connection *conn, const char *msg) {
	size_t len = strlen (msg);
	int sent = 0;
	int packet;
	
	do {
		packet = send (conn -> sock.fd, msg + sent, len - sent, 0);
		
		if (packet >= 0)
			sent += packet;
	} while (sent < len);
	
	// send the \r\n
	const char *rn = { '\r', '\n' };
	len = 2;
	sent = 0;
	do {
		packet = send (conn -> sock.fd, rn + sent, len - sent, 0);
		
		if (packet >= 0)
			sent += packet;
	} while (sent < len);
}

void sendfmtmsg (IRC_Connection *conn, const char *fmt, ...)
	{	FMT_VA (msg);	sendmsg (conn, msg);	}

void IRC_Send (IRC_Channel *chan, const char *msg)
	{	sendfmtmsg (chan, "PRIVMSG %s :%s", chan -> chan_name, msg);	}
void IRC_SendF (IRC_Channel *chan, const char *fmt, ...)
	{	FMT_VA (msg);	IRC_Send (chan, msg);	}

void IRC_SendCmd (IRC_Channel *conn, const char *cmdline)
	{	sendmsg (conn, cmdline);	}
void IRC_SendCmdF (IRC_Channel *conn, const char *fmt, ...)
	{	FMT_VA (msg);	sendmsg (conn, msg);	}

void IRC_JoinChannel (IRC_Channel *chan)
	{	IRC_SendCmdF (chan -> conn, "JOIN %s", chan -> chan_name);	}
void IRC_JoinChannelByName (IRC_Connection *conn, const char *chan)
	{	IRC_SendCmdF (conn, "JOIN %s", chan);	}
