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
		"*disappears into nothingness*",
		"*vanishes into thin air*",
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
	MESSAGELIST (Insult,
		"shut the fuck up",
		"you want me to insult you, huh. i guess i should, since your ego is so high.",
		"\"you bowl of soup.\" -- taswelll",
		"sorry, i dont speak idiot",
		"every word that you utter makes me lose faith in humanity just a little bit more",
		"shut up parentless dumbass",
		"your intellect is off the charts! negatively, i mean.",
		"shut up julian",
		"shup up rust user",
		"ok kit",
		"why dont you shut up before you make a fool of yourself, okay?",
		"why",
		"ive got a ton of insults i could use against you, but i dont know which one to pick..."
		"youre so lonely that im almost inclined to feel sorry for you, but then i remember how much of a loser you are",
		"your face is a face ive been avoiding for seven years; if i have to see it again, ill break down for sure",	// thx cyan
		"leave me alone, please",
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

COMMAND (kitjoin) {
	char *join_ch;
	KB_GetArg (msg, join_ch);
	IRC_Channel *newch;
	
	IRC_JoinChannelByName (chan -> conn, join_ch, &newch);
	IRC_Send (chan, KB_RandMessage (Messages.Confirmation));
	IRC_Send (&newch, KB_RandMessage (Messages.Confirmation));
}

COMMAND (kitinsult) {
	IRC_Send (chan, KB_RandMessage (Messages.Insult));
}
