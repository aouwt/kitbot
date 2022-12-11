#define NO_INSULTING_INSULTS

#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include <irc.h>
#include <kb.h>
#include <libthe.h>
#include <msg.h>
#include <facts.h>

#define SEND(msg)	IRC_Send (&ctx->ch, msg)
#define SENDF(fmt, ...)	IRC_SendF (&ctx->ch, fmt, __VA_ARGS__)
#define RANDMSG(name)	SEND (KB_RandMessage (KB_MESSAGELIST (name)))

#define USES_ARG	char *_last = msg;
#define GETARG	KB_PullArg (&_last);
char *cursource;
FILE *todo;

KB_ON_INIT {
	the_init (&the_source_google);
	cursource = "google";
	todo = fopen ("todo.txt", "a");
}
KB_ON_CLEANUP {
	fclose (todo);
	the_deinit ();
}


KB_ON_COMMAND (kitping) {
	SEND ("kitpong");
}

KB_ON_COMMAND (kitasdf) {
	SEND (KB_Keymash ());
}

KB_ON_COMMAND (kitbot) {
	SEND (KB_Keymash ());
}

KB_ON_COMMAND (kitfact) {
	const char **facts;
	const char *name;
	
	if (strncasecmp (msg, "bee", 3) == 0) {
		name = "bees";
		facts = KB_MESSAGELIST (Fact_Bees);
	} else
	if (strncasecmp (msg, "kit", 3) == 0) {
		name = "kit";
		facts = KB_MESSAGELIST (Fact_Kit);
	} else {
		RANDMSG (NoSuchFact);
		return;
	}
	
	SENDF ("fun fact about %s: %s", name, KB_RandMessage (facts));
}

KB_ON_COMMAND (kittodo) {
	fprintf (todo, " - %s\n", msg);
	fflush (todo);
	RANDMSG (Confirmation);
}
/*
COMMAND (kitjoin) {
	char *join_ch;
	KB_GetArg (msg, join_ch);
	IRC_Channel *newch;
	
	IRC_JoinChannelByName (text->chan->conn, join_ch, &newch);
	IRC_Send (text->chan, KB_RandMessage (KB_MESSAGELIST (Confirmation)));
	IRC_Send (&newch, KB_RandMessage (KB_MESSAGELIST (Confirmation)));
}*/

KB_ON_COMMAND (kitinsult) {
	RANDMSG (Insult);
}

KB_ON_COMMAND (kitsay) {
	IRC_Send (&ctx->ch, msg);
}

/*
#define KITSET_KEYFUNC(name, adminreq)	\
	const bool _kitset_admin ## name = adminreq;	\
	const char *_kitset_keyfunc ## name (char *_last)

#define KITSET_KEYVAL(name)	_kitset_key ## name

#define KITSET_BOOLIF(arg, tf)	\
	tf ? ( \
		strcasecmp (arg, "yes") ||	\
		strcasecmp (arg, "y") ||	\
		strcasecmp (arg, "true") ||	\
		strcasecmp (arg, "t") ||	\
		strcasecmp (arg, "on") ||	\
		strcasecmp (arg, "1")	\
	) : (	\
		strcasecmp (arg, "no") ||	\
		strcasecmp (arg, "n") ||	\
		strcasecmp (arg, "false") ||	\
		strcasecmp (arg, "f") ||	\
		strcasecmp (arg, "off") ||	\
		strcasecmp (arg, "0")	\
	)
KITSET_KEYFUNC (false, the_source) {
	char *arg = GETARG;
	if (strcasecmp (arg, "wikipedia") == 0) {
		the_setsource (&the_source_wikipedia);
		return "wikipedia";
	} else
	if (strcasecmp (arg, "google") == 0) {
		the_setsource (&the_source_google);
		return "google";
	} else
	if (strcasecmp (arg, "bing") == 0) {
		the_setsource (&the_source_bing);
		return "bing";
	} else {
		RANDMSG (Error);
		return NULL;
	}
}

#define SETBOOLIF(what)	\
	char *arg = GETARG;	\
	if (KITSET_BOOLIF (arg, true)) {	\
		what = true;	\
		return "true";	\
	} else	\
	if (KITSET_BOOLIF (arg, false)) {	\
		what = false;	\
		return "false";	\
	} else {	\
		return NULL;	\
	}
	
KITSET_KEYFUNC (true, insult_offensive)
	{ SETBOOLIF (kitinsult_offensive); }

KITSET_KEYFUNC (true, insult_bees)
	{ SETBOOLIF (kitinsult_bees); }

#define KITSET_KEY(name)	{ _kitset_keyfunc ## name, _kitset_admin ## name, NULL, # name }
KB_ON_COMMAND (kitset) { USES_ARG;
	const struct {
		const char *name;
		const char *set;
		bool admin;
		char (*func) (char *);
	} keys [] = {
		KITSET_KEY (libthe_source),
		{ NULL, false, NULL, NULL }
	};
	
	
	char *key = GETARG;
	if (strcasecmp (key, "list") == 0) {
		for (size_t i = 0; keys [i].func != NULL; i ++) {
			SENDF ("%c%s = %s", keys [i].admin ? '!' : '\0', keys [i].name, keys [i].set);
		}
		return;
	}
	RANDMSG (Confirmation);
}*/













KB_ON_COMMAND (kitthe) { USES_ARG;
	
	char buf [64];
	char *term = GETARG;
	the_t the = the_getthe (term);
	if (the == 0) {
		if (strcmp (cursource, "bing") == 0)
			RANDMSG (BingErr);
		else
			RANDMSG (Error);
	} else {
		the_thetostr (the, buf, 64);
		SENDF ("according to %s, \"%s\" is %s (%.10Lf the(s))", cursource, term, buf, the);
	}
}

KB_ON_COMMAND (kithelp) { USES_ARG;
	char *arg = GETARG;
	if (arg == NULL) {
		SEND ("kitbot: dumbest bot in the universe");
		for (size_t i = 0; _KB_C_List [i].run != NULL; i ++) {
			SENDF ("kit%s: %s", _KB_C_List [i].name, _KB_C_List [i].desc);
		}
	} else {
		for (size_t i = 0; _KB_C_List [i].run != NULL; i ++) {
			if (strcasecmp (arg, _KB_C_List [i].name) == 0) {
				SENDF ("kit%s: %s", _KB_C_List [i].name, _KB_C_List [i].help);
				return;
			}
		}
	}
}

KB_ON_COMMAND (kitadmin) { //USES_ARG;
	if (strcmp (ctx->from.full, "kit!~Thunderbird@localhost") == 0) {
		KB_EstablishConnection (msg);
	} else
		RANDMSG (InsufficientPerms);
}


KB_COMMANDLIST (
	{	"ping",
		"play a game of ping pong!",
		"replies \"pong\"",
		kitping
	},
	/*{	"bot",
		NULL,
		NULL,
		kitbot
	},*/
	{	"insult",
		"insults you.",
		"replies with a random insult",
		kitinsult
	},
	{	"fact",
		"fun facts",
		"tells you a fun fact about the given topic. valid topics are bees, kit.",
		kitfact
	},
	{	"the",
		"libthe frontend",
		"print the *the* measurement of a given word or phrase. see https://github.com/aouwt/libthe for more details",
		kitthe
	},
	/*{	"the_source",
		"sets source for kitthe",
		"sets the source for libthe. can be wikipedia, google, or bing.",
		kitthe_source
	},*/
	{	"say",
		"says something",
		"says whatever follows the command",
		kitsay
	},
	{	"help",
		"prints a help message",
		"prints a list of commands, if no argument is supplied. if an argument is supplied, it prints a more detailed explanation on the command given. the prefix included in the command is optional.",
		kithelp
	},
	{	"todo",
		"adds to the todo list",
		"adds the thing you say to the \"todo\" list -- a list stored on the host's computer of things, well, to do.",
		kittodo
	}
);
