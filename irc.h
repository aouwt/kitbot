#ifndef IRC_H
	#define IRC_H
	
	#include <stddef.h>
	
	struct _IRC_UserModes;
	struct _IRC_ChannelModes;
	struct _IRC_User;
	struct _IRC_Channel;
	struct _IRC_Connection;
	struct _IRC_Command;
	
	typedef struct _IRC_Command {
		struct _IRC_Connection *from;
		unsigned int argc;
		char *argv [16];
		char *msg [510];
	} IRC_Command;

	typedef struct _IRC_UserModes {
		char text [5];
		signed char i, s, w, o;
	} IRC_UserModes;

	typedef struct _IRC_ChannelModes {
		char text [12];
		signed char o, s, p, n, m, i, t, l, b, v, k;
	} IRC_ChannelModes;

	typedef struct _IRC_User {
		char nick [16];
		char full [128];
		//struct _IRC_User_Modes mode;
	} IRC_User;

	typedef struct _IRC_Channel {
		char chan_name [16];
		//struct _IRC_User **users;
		struct _IRC_Connection *conn;
		//struct _IRC_ChannelModes mode;
	} IRC_Channel;

	typedef struct _IRC_Message {
		char msg [500];
		struct _IRC_User from;
		struct _IRC_Channel ch;
	} IRC_Message;
	
	typedef struct _IRC_Connection {
		int sockfd;
		char *domain;
		unsigned short port;
		//struct addrinfo *addrinfo;

		IRC_User me;
		
		//const char *motd;
		
		struct {
			size_t alloc;
			char *bufend;
			char *buf;
		} buf;
		
	} IRC_Connection;


	extern void IRC_Poll	(IRC_Connection *conn);	// polls for new messages
	extern void IRC_Send	(IRC_Channel *chan, const char *msg);	// Send message to channel
	extern void IRC_SendF	(IRC_Channel *chan, const char *fmt, ...);	// Send message to channel (printf)
	extern void IRC_SendToCh	(IRC_Connection *conn, const char *chan, const char *msg);	// Send message to channel by name
	extern void IRC_SendToChF	(IRC_Connection *conn, const char *chan, const char *fmt, ...);	// Send message to channel by name (printf)

	extern void IRC_SendCmd	(IRC_Connection *conn, const char *cmdline);	// Send IRC command
	extern void IRC_SendCmdF	(IRC_Connection *conn, const char *fmt, ...);	// Send IRC command (printf)

	extern void IRC_SetNick	(IRC_Connection *conn, const char *nick);	// sets nickname

	extern void IRC_JoinChannel	(IRC_Channel *chan);	// Join channel
	extern void IRC_JoinChannelByName	(IRC_Connection *conn, const char *chan);	// Join channel by name
	
	extern IRC_Command *IRC_GetCommand (IRC_Connection *conn, IRC_Command *out);
	extern IRC_Message *IRC_GetMessage (IRC_Connection *conn, IRC_Message *out);
	extern IRC_Message *IRC_GetPRIVMSG (IRC_Command *cmd, IRC_Message *out);

	extern IRC_Connection *IRC_AllocConnection	(const char *domain, unsigned int port); // allocates IRC_Connection
	extern IRC_Connection *IRC_OpenConnection	(IRC_Connection *conn);	// establishes a connection to the IRC server
	extern IRC_Connection *IRC_SetupConnection	(IRC_Connection *conn, const char *name);	// sets up the connection to IRC server
	extern IRC_Connection *IRC_NewConnection	(IRC_Connection *conn, const char *domain, unsigned int port, const char *name);	// allocates, opens, and sets up new connection
#endif
