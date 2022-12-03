#ifndef KB_H
	#define KB_H
	
	char *KB_Keymash (void);	// generates "fkhdasjkdfajkfhl" or something similar
	char *KB_KeymashFmt (const char *fmt);	// does stuff i think
	
	const char *KB_RandMessage (const char **msgs);	// prints a random message from the list provided
#endif
