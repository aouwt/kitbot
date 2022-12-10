#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <time.h>

#include <irc.h>
#include <kb.h>

char *KB_Keymash (void) {
	const char samples [] =
		"fkdasjgfdklajfoiajeglkdgjmeriaojfkmglkjfalkjfdlfjisadkgjeriosdfjkjgerm"
		"kdskjgfklsjfdlisjgkeriodsljklfksjfklahfauikhfniaukhiufahfdjksafnkldajh"
		"ciukshfncjkdhncukjshidulafhiuehfnvjdkcnjdkafhiudjkafiueldsjafhkljadhkj"
		"lfhdalhfdfafhalkhjadlfhjdsklahfiuahcdjnfajkhkafjldashflhdujafhweudsijk"
		"njfkdhafkljdhjakfhdjkalfhdjkalhfjkdlhalkfdjahfuilrhgfdfjghjkfghfjkgkla"
		"ghfkjzhgfgkhfjkhgajdasfhksdfljghhdfhdfhkfgfvhaagahuaifaegdhgudhgshgeig"
		"jsdkfkdhsgfjdksghkjhflkjhgksjdhfkjshlgfhjsklghfjkshgkjshgkjlahlkfhsjsg"
		"fsdlgkjdsklhgfkslhgjklhsjkfhklasfhjklfjlfjfkjlhjdklhsgfhgklhgkfjhkshjk"
		"ghsgkjhdkufjxdfhusgjkfhnsuijdkghufjkdfhfiujksdhfnivjkdhvudsfjkhjklhdfj"
		"lkhvnkjvkxkkjdfhssghlkdsfjhfkljgdsfhklfjsgslihghiltghegaeriaererdfdjgf"
		"kdslhgfuihngskfjnsgijvkfsgniufjkgnkjlgskjlhgfhlsgkjflghfjksghjfksghjkh"
		"jkfdnjkdhfjljasifjiskdfkjkdsfhvjkdslghfiukdhjfhsglfjsgksjkghiufkjdgkls"
		"huilgesriudfijfklhgsfuighifudlshkgfjsdhgiushglfjkhkgjldfhiudhguidfjkls"
		"hgvukljsdghiuvfksghjdfjkvhlksjdfghilsukhiufdkjngkjldhfskjflhglsdfhdfkl"
		"sguitlruifjdsgjlkjfhlskhgdjsfnksjnfjvknfvkjdnfkdsjfkdshgeuisdfjkhgjkdf"
		"snfjklshefdjkgshkvjldfhnjkldhgedsuihkglsdhgjkfljahgfdjkdlhdfjklshfjklg"
		"hfsjkghlskhfgjkhsjkhfsjkdlhfjkslghsfjklhgjkhsgkighurjdkgnjklfdsnvjkfdh"
		"ngksjhgkljlkshgdufjkgvhdjkvnsfjkghksdjflgfhkxmcnxj"
	;
	const size_t len = sizeof (samples) / sizeof (*samples);
	
	return strndup (
		(size_t) ((float) rand () * ((float) len / (float) RAND_MAX)) + (char *) samples, // pos
		rand () * ((float) 64 / (float) RAND_MAX) + 8 // len, minimum is 8 chrs
	);
}

char *KB_KeymashFmt (const char *fmt) {
	char *mash = KB_Keymash ();
	char *out = malloc ((strlen (fmt) - 1) + strlen (mash));
	
	sprintf (out, fmt, mash);
	free (mash);
	return out;
}

const char *KB_String (const char *str) {
	if (strncmp (str, "!km", 3) == 0)
		return KB_KeymashFmt (str + 3);
	else
		return str;
}

const char *KB_RandMessage (const char **msgs) {
	size_t i;
	for (i = 0; msgs [i] != NULL; i ++);
	
	size_t m = ((float) rand () / (float) RAND_MAX) * (float) i;
	
	return KB_String (msgs [m]);
}

void KB_CallCmd (const char *cmd, const char *msg, IRC_Message *ctx) {
	if (msg == NULL)
		msg = ctx->msg;
	
	for (struct KB_Command *i = _KB_C_List; i->run != NULL; i ++) {
		if (strcmp (cmd, i->name) == 0) {
			(*i->run) (msg, ctx);
			return;
		}
	}
}
