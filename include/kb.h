#ifndef KB_H
	#define KB_H
	
	#include <stddef.h>
	#include <irc.h>
	
	#define KB_COMMANDLIST(...)	struct KB_Command _KB_C_List [] = { __VA_ARGS__, { NULL, NULL, NULL, NULL }};

	#define KB_ON_COMMAND(name)	void name (char *msg, IRC_Message *ctx)
	#define KB_ON_INIT	void _KB_C_Init (void)
	#define KB_ON_CLEANUP	void _KB_C_Cleanup (void)

	#define KB_DEFMESSAGELIST(name, ...)	const char *_KB_MsgList_ ## name [] = { __VA_ARGS__, NULL };
	#define KB_MESSAGELIST(name)	_KB_MsgList_ ## name
	#define KB_CONST_KEYMASH(fmt)	"!km" fmt
	
	
	struct KB_Command {
		const char *name;
		const char *desc;
		const char *help;
		void (*run) (char *msg, IRC_Message *ctx);
	};
	
	extern IRC_Connection **KB_Connections;
	extern size_t KB_ConnectionsCnt;

	extern IRC_Connection *KB_EstablishConnection (const char *server);
	
	extern char *KB_Keymash (void);	// generates "fkhdasjkdfajkfhl" or something similar
	extern char *KB_KeymashFmt (const char *fmt);	// does stuff i think
	
	extern const char *KB_RandMessage (const char **msgs);	// prints a random message from the list provided
	
	extern void KB_CallCmd (const char *cmd, char *msg, IRC_Message *ctx);
	
	extern char *KB_PullArg (char **last);
	
	// --- VALUES PROVIDED BY USER ---
	extern void _KB_C_Init (void);
	extern void _KB_C_Cleanup (void);
	extern struct KB_Command _KB_C_List [];
	
#endif
