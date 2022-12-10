#include "msg.h"
#include <kb.h>

KB_DEFMESSAGELIST (Quotes,
	"\"you bowl of soup\" -- taswelll",
	KB_CONST_KEYMASH ("\"%s\" -- kitbot")
);
KB_DEFMESSAGELIST (YourMomJokes,
	"your mom is so fat, she has more chins than a chinese phonebook",
	"your mom.",
	"your mom is so dumb that she decided to raise you.",
	"ur mom",
	KB_CONST_KEYMASH ("your mom is so dumb that she %s")
);
