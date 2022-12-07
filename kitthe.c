#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
CURL *curl;

typedef unsigned long long thecnt_t;
typedef long double the_t;

thecnt_t the_thes;

const struct the_unit {
	the_t the;
	const char *name;
} the_units [] = {
	{ 0.000000000000000000000000000001, "quectothe" },
	{ 0.000000000000000000000000001, "rontothe" },
	{ 0.000000000000000000000001, "yoctothe" },
	{ 0.000000000000000000001, "zeptothe" },
	{ 0.000000000000000001, "attothe" },
	{ 0.000000000000001, "femtothe" },
	{ 0.000000000001, "picothe" },
	{ 0.000000001, "nanothe" },
	{ 0.000001, "microthe" },
	{ 0.001, "millithe" },
	{ 0.01, "centithe" },
	{ 0.1, "decithe" },
	{ 1.0, "the" },
	{ 10.0, "decathe" },
	{ 100.0, "hectothe" },
	{ 1000.0, "kilothe" },
	{ 1000000.0, "megathe" },
	{ 1000000000.0, "gigathe" },
	{ 1000000000000.0, "terathe" },
	{ 1000000000000000.0, "petathe" },
	{ 1000000000000000000.0, "exathe" },
	{ 1000000000000000000000.0, "zettathe" },
	{ 1000000000000000000000000.0, "yottathe" },
	{ 1000000000000000000000000000.0, "ronnathe" },
	{ 1000000000000000000000000000000.0, "quettathe" },
	{ 0, NULL }
};

struct the_source {
	char firstchar;
	const char *fmat;
	const char *url;
};

static const struct the_source the_source_google = {
	'<',
	"div id=\"result-stats\">About %m[0-9,] results",
	"https://www.google.com/search?q=\"%s\""
};

static const struct the_source the_source_wikipedia = {
	'{',
	"\"totalhits\":%m[0-9],",
	"https://en.wikipedia.org/w/api.php?action=query&list=search&format=json&srwhat=text&srsearch=\"%s\""
};

static const struct the_source the_source_bing = {
	 '<',
	 "span class=\"sb_count%*[^>]>About %m[0-9,] results",
	 "https://www.bing.com/search?q=\"%s\""
};

struct the_source the_currentsource;

thecnt_t the_atothecnt_ignore (const char *str) {
	thecnt_t out = 0;
	for (size_t i = 0; str [i] != '\0'; i ++) {
		if (str [i] >= '0' && str [i] <= '9')
			out = out * 10 + str [i] - '0';
	}
	return out;
}

thecnt_t the_getcnt (const char *term) {
	FILE *f = tmpfile ();
	if (f == NULL)
		return 0;
	curl_easy_setopt (curl, CURLOPT_WRITEDATA, f);
	
	static char tmp [512];
	snprintf (tmp, sizeof (tmp) / sizeof (tmp [0]), the_currentsource.url, term);
	curl_easy_setopt (curl, CURLOPT_URL, tmp);
	
	if (curl_easy_perform (curl))
		return 0;
	
	rewind (f);
	while (1) {
		int c = fgetc (f);
		if (c == EOF)
			return 0;
		if (c == the_currentsource.firstchar) {
			char *outstr;
			if (fscanf (f, the_currentsource.fmat, &outstr) == 1) {
				fclose (f);
				thecnt_t out = the_atothecnt_ignore (outstr);
				free (outstr);
				return out;
			}
		}
	}
}

the_t the_getthe (const char *term) {
	if (the_thes == 0) {
		return 0;
	}
	return (the_t) the_getcnt (term) / (the_t) the_thes;
}

the_t the_inunit (the_t the, the_t unit) {
	return the / unit;
}

struct the_unit the_getthe_unit (the_t thes) {
	struct the_unit out;
	
	if (thes == 0) {
		out.the = 0;
		out.name = "the";
		return out;
	}
	
	the_t inunit = the_inunit (thes, the_units [0].the);
	if (inunit <= 1) {
		out.the = inunit;
		out.name = the_units [0].name;
		return out;
	}
	
	size_t i = 1;
	while (1) {
		inunit = the_inunit (thes, the_units [i].the);
		if (inunit < 1) {
			out.the = the_inunit (thes, the_units [i - 1].the);
			out.name = the_units [i - 1].name;
			break;
		} else
		if (the_units [i + 1].name == NULL) {
			out.the = inunit;
			out.name = the_units [i].name;
			break;
		} else
			i ++;
	}
	
	return out;
}


void the_thetostr (the_t the, char *buf, size_t maxlen) {
	struct the_unit unit = the_getthe_unit (the);
	snprintf (buf, maxlen, "%Lf %s%c", unit.the, unit.name, (unit.the == 1) ? '\0' : 's');
}

void the_setsource (struct the_source *source) {
	the_currentsource = *source;
	the_thes = the_getcnt ("the");
}

void the_init (void) {
	curl_global_init (CURL_GLOBAL_ALL);
	curl = curl_easy_init ();
	
	curl_easy_setopt (curl, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; Linux x86_64; rv:102.0) Gecko/20100101 Firefox/102.0");
	
	//the_setsource (&the_source_google);
}

void print_thes (const char *name, const char *term) {
	char buf [512];
	the_t the = the_getthe (term);
	the_thetostr (the, buf, 512);
	printf ("%s: %s (%.20Lf thes)\n", name, buf, the);
}

void main (int argc, char **argv) {
	the_init ();
	
	printf ("thes found for term \"%s\"\n", argv [1]);
	
	the_setsource (&the_source_bing);
	print_thes ("bing", argv [1]);
	
	the_setsource (&the_source_google);
	print_thes ("google", argv [1]);
	
	the_setsource (&the_source_wikipedia);
	print_thes ("wikipedia", argv [1]);
}
