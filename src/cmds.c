#define NO_INSULTING_INSULTS

#include <string.h>
#include <stdio.h>

#include <irc.h>
#include <kb.h>
#include <libthe.h>
#include <msg.h>
#include <facts.h>

#define SEND(msg) IRC_Send (&ctx->ch, msg)
#define SENDF(fmt, ...) IRC_SendF (&ctx->ch, fmt, __VA_ARGS__)
#define RANDMSG(name) SEND (KB_RandMessage (KB_MESSAGELIST (name)))

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

KB_ON_COMMAND (kitthe_source) {
	if (strcasecmp (msg, "wikipedia") == 0) {
		the_setsource (&the_source_wikipedia);
		cursource = "wikipedia";
	} else
	if (strcasecmp (msg, "google") == 0) {
		the_setsource (&the_source_google);
		cursource = "google";
	} else
	if (strcasecmp (msg, "bing") == 0) {
		the_setsource (&the_source_bing);
		cursource = "bing";
	} else {
		RANDMSG (Error);
		return;
	}
	
	RANDMSG (Confirmation);
}

KB_ON_COMMAND (kitthe) {
	char buf [64];
	the_t the = the_getthe (msg);
	if (the == 0) {
		if (strcmp (cursource, "bing") == 0)
			RANDMSG (BingErr);
		else
			RANDMSG (Error);
	} else {
		the_thetostr (the, buf, 64);
		SENDF ("according to %s, \"%s\" is %s (%.10Lf the(s))", cursource, msg, buf, the);
	}
}

KB_ON_COMMAND (kithelp) {
	SEND ("kitbot: dumbest bot in the universe");
	for (size_t i = 0; _KB_C_List [i].run != NULL;  i ++) {
		SENDF ("kit%s: %s", _KB_C_List [i].name, _KB_C_List [i].desc);
	}
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
	{	"the_source",
		"sets source for kitthe",
		"sets the source for libthe. can be wikipedia, google, or bing.",
		kitthe_source
	},
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
