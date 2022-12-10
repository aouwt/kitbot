#include "msg.h"
#include <kb.h>

KB_DEFMESSAGELIST (BingErr,
	"*sigh* bing is being bing",
	"fuck microsoft",
	KB_CONST_KEYMASH ("%s")
)
KB_DEFMESSAGELIST (Joining,
	"howdy howdy howdy",
	"wazzup NERDS",
	"hello",
	"howdy",
	KB_CONST_KEYMASH ("%s")
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
	KB_CONST_KEYMASH ("%s")
);
KB_DEFMESSAGELIST (Leaving,
	"see ya, suckers",
	"haha BYE",
	"see yall in HELL",
	"bye",
//	"*disappears into nothingness*",
//	"*vanishes into thin air*",
	KB_CONST_KEYMASH ("my final word: %s"),
	KB_CONST_KEYMASH ("%s")
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
	KB_CONST_KEYMASH ("there was an error: %s")
);
KB_DEFMESSAGELIST (NoSuchFact,
	"what the fuck is that",
	"huh...?",
	"idk what that is",
	KB_CONST_KEYMASH ("%s")
);
KB_DEFMESSAGELIST (InsufficientPerms,
	"haha loser, you think you can make me do that?",
	"im not going to listen to you",
	"why should i",
	"come back when you have actual authority",
	"no.",
	"i dont wanna",
	"shut up",
	KB_CONST_KEYMASH ("%s")
);
