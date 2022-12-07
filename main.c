#include "irc.h"
#include "kb.h"
#include <stddef.h>
#include <stdio.h>


void main (void) {
	IRC_Connection *conn = IRC_NewConnection (NULL, "irc.osmarks.net", 0, "kitbot");
	if (conn == NULL)
		puts (KB_Keymash ());
	
	IRC_SetNick (conn, "kitbot");

	IRC_JoinChannelByName (conn, "#b");
	
	IRC_SendToCh (conn, "#b", "test");
	static IRC_Message msg;
	while (1) {
		if (IRC_GetMessage (conn, &msg) != NULL)
			printf ("<%s> %s\n", msg.from.nick, msg.msg);
	}
}
