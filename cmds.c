struct Command {
	const char *name;
	const char *desc;
	const char *help;
	void (*run) (const char *msg, const char *fullmessage, IRC_Channel *chan);
};


struct Command _KB_C_CList [] {
	{	"ping",
		"play a game of ping pong!",
		"replies \"pong\"",
		kitping
	},
	{	"insult",
		"insults you.",
		"replies with a random insult",
		kitinsult
	},
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
	},
	{	"say",
		"says something",
		"says whatever follows the command",
		kitsay
	},
	{	"asdf",
		KB_Keymash (),
		KB_Keymash (),
		kitasdf
	}
	{	"help",
		"prints a help message",
		"prints a list of commands, if no argument is supplied. if an argument is supplied, it prints a more detailed explanation on the command given. the prefix included in the command is optional.",
		kithelp
	},
	NULL
};

#define COMMAND(name)	void name (const char *msg, const char *fullmessage, IRC_Channel *chan)
#define INIT	void _KB_C_Init (void)
#define CLEANUP	void _KB_C_Cleanup (void)

#define MESSAGELIST(name, ...)	char *name [] = { __VA_ARGS__, NULL }


struct {
	MESSAGELIST (Joining,
		"howdy howdy howdy",
		"wazzup NERDS",
		"hello",
		"howdy",
		KB_Keymash ()
	);
	MESSAGELIST (Confirmation,
		"okie",
		"okie dokey",
		"ugh, fine",
		"sure",
		"sure, fine, whatever",
		"ok",
		"okay",
		"working on it",
		"ok ok ok ok",
		"whatever you want, asshole",
		KB_Keymash ()
	);
	MESSAGELIST (Leaving,
		"see ya, suckers",
		"haha BYE",
		"see yall in HELL",
		"bye",
	//	"*disappears into nothingness*",
	//	"*vanishes into thin air*",
		KB_KeymashFmt ("my final word: %s"),
		KB_Keymash ()
	);
	MESSAGELIST (Error,
		"you absolute fool",
		"you fucking moron",
		"look what youve done",
		"shut up",
		"why must you treat me this way",
		"oopsie",
		
		#ifndef NO_BEES
			"apioform you",
			"bee you",
			"oh bees",
		#endif
		KB_KeymashFmt ("there was an error: %s")
	);
	MESSAGELIST (InsufficientPerms,
		"haha loser, you think you can make me do that?",
		"im not going to listen to you",
		"why should i",
		"come back when you have actual authority",
		"no.",
		"i dont wanna",
		"shut up",
		KB_Keymash ()
	);
	MESSAGELIST (Insult,
		"shut the fuck up",
		"you want me to insult you, huh. i guess i should, since your ego is so high.",
		"\"you bowl of soup.\" -- taswelll",
		"sorry, i dont speak idiot",
		"every word that you utter makes me lose faith in humanity just a little bit more",
		"shut up parentless dumbass",
		"your intellect is off the charts! negatively, i mean.",
	//	"shut up julian",
		"shup up rust user",
	//	"ok kit",
		"why dont you shut up before you make a fool of yourself, okay?",
		"why",
		"ive got a ton of insults i could use against you, but i dont know which one to pick..."
		"youre so lonely that im almost inclined to feel sorry for you, but then i remember how much of a loser you are",
		"your face is a face ive been avoiding for seven years; if i have to see it again, ill break down for sure",	// thx cyan
		"leave me alone, please",
		"you are like a beer keg except youre full of useless questions instead of beer",
		KB_KeymashFmt ("\"%s\" -- what i hear whenever you talk"),
		
		#ifndef NO_INSULTING_INSULTS
			"why do you even try to live if youre this much of a failure.",
			"sorry, i dont speak failure",
			"you fucking disgrace",
			"you are a menace to society",
			"nobody likes you",
			"i hope you die in a hole one day, if you can even fit in one",
			"i hope i never see you again",
		#endif
		
		#ifndef GOOD_INSULTS
		
			#ifndef NO_BEES
				"bee you",
				"you utter bee",
				"apioform you",
				"you utter apioform"
			#endif
			
			"sussy baka",
		#endif
		
		KB_Keymash ()
	);
	MESSAGELIST (Quotes,
		"\"you bowl of soup\" -- taswelll",
		KB_KeymashFmt ("\"%s\" -- kitbot")
	);
	MESSAGELIST (YourMomJokes,
		"your mom is so fat, she has more chins than a chinese phonebook",
		"your mom.",
		"your mom is so dumb that she decided to raise you.",
		"ur mom",
		KB_KeymashFmt ("your mom is so dumb that she %s")
	)
} Messages

INIT {}
CLEANUP {}


COMMAND (kitping) {
	IRC_Send (chan, "kitpong");
}

COMMAND (kitasdf) {
	IRC_Send (chan, KB_Keymash ());
}

COMMAND (kitjoin) {
	char *join_ch;
	KB_GetArg (msg, join_ch);
	IRC_Channel *newch;
	
	IRC_JoinChannelByName (chan->conn, join_ch, &newch);
	IRC_Send (chan, KB_RandMessage (Messages.Confirmation));
	IRC_Send (&newch, KB_RandMessage (Messages.Confirmation));
}

COMMAND (kitinsult) {
	IRC_Send (chan, KB_RandMessage (Messages.Insult));
}
