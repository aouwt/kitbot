#include <irc.h>
#include <kb.h>
#include <libthe.h>

#include <string.h>

#include <msg.h>
#include <facts.h>

#define NO_INSULTING_INSULTS


char *cursource;

KB_ON_INIT {
	the_init (&the_source_google);
	cursource = "google";
}
KB_ON_CLEANUP {
}


KB_ON_COMMAND (kitping) {
	IRC_Send (&ctx->ch, "kitpong");
}

KB_ON_COMMAND (kitasdf) {
	IRC_Send (&ctx->ch, KB_Keymash ());
}

KB_ON_COMMAND (kitbot) {
	IRC_Send (&ctx->ch, KB_Keymash ());
}

KB_ON_COMMAND (kitbeefact) {
	IRC_Send (&ctx->ch, KB_RandMessage (KB_MESSAGELIST (Fact_Bees)));
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
	IRC_Send (&ctx->ch, KB_RandMessage (KB_MESSAGELIST (Insult)));
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
		IRC_Send (&ctx->ch, KB_RandMessage (KB_MESSAGELIST (Error)));
		return;
	}
	
	IRC_Send (&ctx->ch, KB_RandMessage (KB_MESSAGELIST (Confirmation)));
}

KB_ON_COMMAND (kitthe) {
	char buf [64];
	the_t the = the_getthe (msg);
	if (the == 0) {
		if (strcmp (cursource, "bing") == 0)
			IRC_Send (&ctx->ch, KB_RandMessage (KB_MESSAGELIST (BingErr)));
		else
			IRC_Send (&ctx->ch, KB_RandMessage (KB_MESSAGELIST (Error)));
	} else {
		the_thetostr (the, buf, 64);
		IRC_SendF (&ctx->ch, "according to %s, \"%s\" is %s (%.10Lf the(s))", cursource, msg, buf, the);
	}
}

KB_ON_COMMAND (kithelp) {
	IRC_Send (&ctx->ch, "kitbot: dumbest bot in the universe");
	for (size_t i = 0; _KB_C_List [i].run != NULL;  i ++) {
		IRC_SendF (&ctx->ch, "kit%s: %s", _KB_C_List [i].name, _KB_C_List [i].desc);
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
	{	"bee",
		"learn about bees!",
		"tells you a fact about bees",
		kitbeefact
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
	/*
	{	"join",
		"joins an IRC channel",
		"joins a channel. channels are presented in the format #<channel>[@<server>]. if no server is provided, it is assumed that the server is the one that has sent the command. based on configuration options, this command might only be sent by channel ops.",
		kitjoin
	},
	{	"sql",
		"execute raw sql queries",
		"executes a raw sql query to a sqlite3 database",
		kitsql
	},
	{	"connect",
		"connect to irc server",
		"connects to an irc server, provided as the rest of the command. based on configuration options, this command might only be sent by channel ops.",
		kitconnect
	},
	{	"leave",
		"leaves an irc channel",
		"leaves the irc channel supplied. channels are in the format #<channel>[@<server>]. if no server is provided, it is assumed that the server is the one that has sent the command. based on configuration options, this command might only be sent by channel ops."
		kitleave
	},
	{	"die",
		"disconnects from an irc server",
		"disconnects from the irc server supplied. if no server is specified, it leaves the server that has sent the command. based on configuration options, this command might only be sent by channel ops.",
		kitdie
	},*/
	{	"say",
		"says something",
		"says whatever follows the command",
		kitsay
	},/*,
	{	"asdf",
		KB_Keymash (),
		KB_Keymash (),
		kitasdf
	},*/
	{	"help",
		"prints a help message",
		"prints a list of commands, if no argument is supplied. if an argument is supplied, it prints a more detailed explanation on the command given. the prefix included in the command is optional.",
		kithelp
	}
);
