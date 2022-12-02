#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <time.h>

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
