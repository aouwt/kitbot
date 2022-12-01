#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

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
		(size_t) (rand () * ((float) RAND_MAX / (float) len)) + (char *) samples, // pos
		(size_t) ((rand () * (RAND_MAX / (len - 8))) + 8) // len, minimum is 8 chrs
	);
}

void main (void) {
	puts (KB_Keymash ());
}
