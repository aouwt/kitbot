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
};

struct _IRC_Connection {
	char *channels_avail [];
	IRC_Channel channels [];

	int sockfd;
	char *domain;
	unsigned short port;
	struct addrinfo *addrinfo;

	IRC_User me;
	
	struct {
		unsigned short id;
		const char *msg;
	} ecodes [20];
	
	const char *motd;
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
		packet = send (conn -> sockfd, msg + sent, len - sent, 0);
		
		if (packet >= 0)
			sent += packet;
	} while (sent < len);
	
	// send the \r\n
	const char *rn = { '\r', '\n' };
	len = 2;
	sent = 0;
	do {
		packet = send (conn -> sockfd, rn + sent, len - sent, 0);
		
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

IRC_Connection *IRC_AllocConnection (const char *domain, unsigned int port) {
	IRC_Connection *out = malloc (sizeof (IRC_Connection));
	
	if (port == 0)
		port = 6667;
	
	out -> channels_avail = NULL;
	out -> channels = NULL;
	out -> sockfd = -1;
	out -> domain = strdup (domain);
	out -> port = port;
	out -> addrinfo = NULL;
	
	return out;
}

IRC_Connection *IRC_OpenConnection (IRC_Connection *conn) {
	if (conn -> addrinfo == NULL) {
		if (getaddrinfo (conn -> domain, NULL, NULL, &conn -> addrinfo))
			return NULL;
	}
	
	if (conn -> sockfd == -1) {
		conn -> sockfd = socket (conn -> addrinfo -> ai_family, conn -> addrinfo -> ai_socktype, conn -> addrinfo -> ai_protocol);
		
		if (conn -> sockfd == -1)
			return NULL;
		
		if (fcntl (sockfd, F_SETFL, O_NONBLOCK))
			return NULL;
		
		((struct sockaddr_in*) conn -> addrinfo -> ai_addr) -> sin_prt = htons (port);
		
		bool cont = false;
		do {
			connect (conn -> sockfd, conn -> addrinfo -> ai_addr, conn -> addrinfo -> ai_addrlen);
			switch (errno) {
				case EINPROGRESS: case EALREADY:
					cont = true;
				break;
				default:
					return NULL;
				break;
			}
		} while (cont);
	}
	
	return conn;
}

IRC_Connection *IRC_SetupConnection (IRC_Connection *conn, const char *name) {
	sendfmtmsg (conn, "USER %s %s %s %s", name, name, domain, name);
	return conn;
}

IRC_Connection *IRC_NewConnection (IRC_Connection *conn, const char *domain, unsigned int port, const char *name) {
	if (conn == NULL)
		conn = IRC_AllocConnection (domain, port);
	
	if (IRC_OpenConnection (conn) == NULL)
		return NULL;
	
	IRC_SetupConnection (conn, name);
}
