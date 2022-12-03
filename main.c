#include "irc.h"
#include "kb.h"
#include <stddef.h>
#include <stdio.h>


void main (void) {
	IRC_Connection *conn = IRC_NewConnection (NULL, "irc.osmarks.net", 6697, "kitbot");
	if (conn == NULL)
		puts (KB_Keymash ());
	
	//IRC_SetNick (conn, "kitbot");

	//IRC_JoinChannelByName (conn, "a");
	
	//IRC_SendToCh (conn, "#a", "test");
	
	while (1)
		IRC_Poll (conn);
}
