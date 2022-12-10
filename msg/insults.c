#include "msg.h"
#include <kb.h>

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
	"ive got a ton of insults i could use against you, but i dont know which one to pick...",
	"youre so lonely that im almost inclined to feel sorry for you, but then i remember how much of a loser you are",
	"your face is a face ive been avoiding for seven years; if i have to see it again, ill break down for sure",	// thx cyan
	"leave me alone, please",
	"you are like a beer keg except youre full of useless questions instead of beer",
	KB_CONST_KEYMASH ("\"%s\" -- what i hear whenever you talk"),
	
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
	
	KB_CONST_KEYMASH ("%s")
);
