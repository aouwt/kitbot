#include "irc.h"
#include "kb.h"



/*
KB_DEFMESSAGELIST (Joining,
	"howdy howdy howdy",
	"wazzup NERDS",
	"hello",
	"howdy",
	KB_Keymash ()
);
KB_DEFMESSAGELIST (Confirmation,
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
KB_DEFMESSAGELIST (Leaving,
	"see ya, suckers",
	"haha BYE",
	"see yall in HELL",
	"bye",
//	"*disappears into nothingness*",
//	"*vanishes into thin air*",
	KB_KeymashFmt ("my final word: %s"),
	KB_Keymash ()
);
KB_DEFMESSAGELIST (Error,
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
KB_DEFMESSAGELIST (NoSuchFact,
	"what the fuck is that",
	"huh...?",
	"idk what that is",
	KB_Keymash ()
);
KB_DEFMESSAGELIST (InsufficientPerms,
	"haha loser, you think you can make me do that?",
	"im not going to listen to you",
	"why should i",
	"come back when you have actual authority",
	"no.",
	"i dont wanna",
	"shut up",
	KB_Keymash ()
);
KB_DEFMESSAGELIST (Insult,
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
KB_DEFMESSAGELIST (Quotes,
	"\"you bowl of soup\" -- taswelll",
	KB_KeymashFmt ("\"%s\" -- kitbot")
);
KB_DEFMESSAGELIST (YourMomJokes,
	"your mom is so fat, she has more chins than a chinese phonebook",
	"your mom.",
	"your mom is so dumb that she decided to raise you.",
	"ur mom",
	KB_KeymashFmt ("your mom is so dumb that she %s")
);
KB_DEFMESSAGELIST (BeeFacts,
	"Bees have 5 eyes (https://honeybeenet.gsfc.nasa.gov/Honeybees/Basics.htm)",
	"Bees are insects, so they have 6 legs (https://honeybeenet.gsfc.nasa.gov/Honeybees/Basics.htm)",
	"Male bees in the hive are called drones (https://honeybeenet.gsfc.nasa.gov/Honeybees/Basics.htm)",
	"Bees fly about 20 mph (https://honeybeenet.gsfc.nasa.gov/Honeybees/Basics.htm)",
	"Female bees in the hive (except the queen) are called worker bees (https://honeybeenet.gsfc.nasa.gov/Honeybees/Basics.htm)",
	"Number of eggs laid by queen: 2,000 per day is the high (https://honeybeenet.gsfc.nasa.gov/Honeybees/Basics.htm)",
	"Losing its stinger will cause a bee to die (https://honeybeenet.gsfc.nasa.gov/Honeybees/Basics.htm)",
	"Bees have been here about 30 million years (https://honeybeenet.gsfc.nasa.gov/Honeybees/Basics.htm)",
	"Bees carry pollen on their hind legs in a pollen basket or corbicula (https://honeybeenet.gsfc.nasa.gov/Honeybees/Basics.htm)",
	"An average beehive can hold around 50,000 bees (https://honeybeenet.gsfc.nasa.gov/Honeybees/Basics.htm)",
	"Foragers must collect nectar from about 2 million flowers to make 1 pound of honey (https://honeybeenet.gsfc.nasa.gov/Honeybees/Basics.htm)",
	"The average forager makes about 1/12 th of a teaspoon of honey in her lifetime (https://honeybeenet.gsfc.nasa.gov/Honeybees/Basics.htm)",
	"Average per capita honey consumption in the US is 1.3 pounds (https://honeybeenet.gsfc.nasa.gov/Honeybees/Basics.htm)",
	"Bees have 2 pairs of wings (https://honeybeenet.gsfc.nasa.gov/Honeybees/Basics.htm)",
	"The principal form of communication among honey bees is through chemicals called pheromones (https://honeybeenet.gsfc.nasa.gov/Honeybees/Basics.htm)",
	"Bees are important because they pollinate approximately 130 agricultural crops in the US including fruit, fiber, nut, and vegetable crops. Bee pollination adds approximately 14 billion dollars annually to improved crop yield and quality. (https://honeybeenet.gsfc.nasa.gov/Honeybees/Basics.htm)",
	"The honey bee has been around for millions of years. (https://www.benefits-of-honey.com/honey-bee-facts/)",
	"Honey bees, scientifically also known as Apis mellifera, which mean “honey-carrying bee”, are environmentally friendly and are vital as pollinators. (https://www.benefits-of-honey.com/honey-bee-facts/)",
	"Honey bees are the only insect that produces food eaten by man. (https://www.benefits-of-honey.com/honey-bee-facts/)",
	"Honey bees have 6 legs, 2 compound eyes made up of thousands of tiny lenses (one on each side of the head), 3 simple eyes on the top of the head, 2 pairs of wings, a nectar pouch, and a stomach. (https://www.benefits-of-honey.com/honey-bee-facts/)",
	"Honey bees have 170 odorant receptors, compared with only 62 in fruit flies and 79 in mosquitoes. Their exceptional olfactory abilities include kin recognition signals, social communication within the hive, and odor recognition for finding food. Their sense of smell is so precise that it could differentiate hundreds of different floral varieties and tell whether a flower carried pollen or nectar from metres away. (https://www.benefits-of-honey.com/honey-bee-facts/)",
	"The honey bee’s wings stroke incredibly fast, about 200 beats per second, thus making their famous, distinctive buzz. A honey bee can fly for up to six miles, and as fast as 15 miles per hour. (https://www.benefits-of-honey.com/honey-bee-facts/)",
	"The average worker bee produces only about 1/12th teaspoon of honey in her lifetime. (https://www.benefits-of-honey.com/honey-bee-facts/)",
	"A hive of bees will fly 90,000 miles, the equivalent of three orbits around the earth to collect 1 kg of honey. (https://www.benefits-of-honey.com/honey-bee-facts/)",
	"A honey bee visits 50 to 100 flowers during a collection trip. (https://www.benefits-of-honey.com/honey-bee-facts/)",
	"The bee’s brain is oval in shape and only about the size of a sesame seed (iflscience.com), yet it has remarkable capacity to learn and remember things and is able to make complex calculations on distance travelled and foraging efficiency. (https://www.benefits-of-honey.com/honey-bee-facts/)",
	"A colony of bees consists of 20,000-60,000 honeybees and one queen. Worker honey bees are female, live for about 6 weeks and do all the work. (https://www.benefits-of-honey.com/honey-bee-facts/)"
);*/

KB_ON_INIT {}
KB_ON_CLEANUP {}


KB_ON_COMMAND (kitping) {
	IRC_Send (&ctx->ch, "kitpong");
}

KB_ON_COMMAND (kitasdf) {
	IRC_Send (&ctx->ch, KB_Keymash ());
}

KB_ON_COMMAND (kitbot) {
	IRC_Send (&ctx->ch, KB_Keymash ());
}
/*
COMMAND (kitjoin) {
	char *join_ch;
	KB_GetArg (msg, join_ch);
	IRC_Channel *newch;
	
	IRC_JoinChannelByName (text->chan->conn, join_ch, &newch);
	IRC_Send (text->chan, KB_RandMessage (KB_MESSAGELIST (Confirmation)));
	IRC_Send (&newch, KB_RandMessage (KB_MESSAGELIST (Confirmation)));
}

COMMAND (kitinsult) {
	IRC_Send (msg->chan, KB_RandMessage (KB_MESSAGELIST (Insult)));
}

COMMAND (kitbeefact) {
	IRC_Send (msg->chan, KB_RandMessage (KB_MESSAGELIST (BeeFacts)));
}*/



KB_COMMANDLIST (
	{	"ping",
		"play a game of ping pong!",
		"replies \"pong\"",
		kitping
	},
	{	"bot",
		NULL,
		NULL,
		kitbot
	}/*,
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
	}*/
);
