#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <time.h>

char *KB_Keymash (void) {
	const char samples [] =
		"jfkdahfkudjhafkjdhlkfjdlkagdfhjkahfkljdhklfdshaklfjhdlkjfhadkslfhilfdiajfd"
		"hklkfhjakflhklajfhkdljahfkjdhkfldhgfdashjenaiusfhjershkresnuifcesriugfhner"
		"siukgvnuisefhniesukhfnuaweijfnciuakfhdijkaflhrkaljfhkfjfhiurahrfjkjfhierua"
		"hyfiurktgnawnclkansjlzhilufhaliutfrslgiuhndjhgneisruldhfuisjlnvjsahsnutila"
		"fjsnduikljfascnzuilkjgomirshnguifkajmiocljanigulkariflcjdnsuilkhnvlkajjrfi"
		"odjasnlfhnailkfnmcoidlzjfnuiakjnflkcdjangfhlranljkfhnclsdihgunifahjngrkanf"
		"uilhtuilndazfjnaluthfiutmfiouesjnfjklhsuilhfurjslgniofdhsgjklndljfosijgihr"
		"iualgfnrlsufdhgsdjklcnzfuiksrhflihjaiouruueoiarujjdkzhflkashafjkhdlahtfrui"
		"lhvnlkdshfniulahkgfnviuakshfuilakkfjdkjhcukalshfailukthiudlkthfieuldahnuil"
		"fhiualthfurilafhljaghuilaeyfhiliytahfpsufijkdusghfauldkhfuilkiagilauhefdla"
		"isughilaitujflaighfiltfjailetujfiuagdrkflrugshlraigugpafslihjfilasdhijtfla"
		"isuhfniauslkhwppeuifjiadlsluirfuiarlsehflicusahtiegulfshgliauvkdsnviuakwfo"
		"jdieufhlskcujdfhudkhfalihiufjkdkiucajguiflaehgikeshgnesrukgniesukgniesugvn"
		"ukjghslifuhnjelahfiurkljgluihslihalihgsvklhrtkguhesrildfgkljdsfghfsulghniu"
		"jkgnjfsdkgnlituksghnilrukgnrifushvniugkjshtiugfhsuigkjhgsluikshgliefrsifdh"
		"suigkhilgukhsviluekhfuikgjhnuiskjvniukshtguirkjhsguifrjkshgivulkjhsgniuels"
		"khfruifhiluiuej8oitufjitukgfhskuhgjlusilhyguishguieslhotiarhuiefyiurrhfdsj"
		"fhkdcnskjdlvjhdsbvuilskjfhrklshnvbsjfhljsbfjklshfjkmkhfijiohjfnoiershnurhd"
		"sghlvishgnnurisjkgnvuilkjshvniuksjgniukjrghiulskgjrhlsdghnruisjghiulskhgli"
		"urshtliuhkgnliusthgsiurkjhgiukdjghiurskghviusghgukjhguorsikhgisukjrghisulg"
		"hniulghsuigklrhigukhdfilughtiogfshiugfshgnuesrilhgfuilhsgfuirhiutlrfhdutil"
		"gkfhiurfkhoighoigtkurtiosupwiturifhsupwuriewpeufrjslhfsufilhtuirhsguirlhis"
		"turilgvuifslgniusfjsiorfhigofsuifsiujoiehjfnsuirlfujiurfhyiutfhjtisorfhtiu"
		"fhgifuktsofltufistehfiuyfhiuwerujoiweryhuirjsfhkufhsiuetyghrsilehgurisygui"
		"srhfuiresityhesruyhfuiejshfuiesrlghisrl"
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

void main (void) {
	srand (time (NULL));
	puts (KB_Keymash ());
}
