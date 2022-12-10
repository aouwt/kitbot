#define _GNU_SOURCE

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#include <irc.h>
#include <kb.h>


int main (void) {
	srand (time (NULL));
	{
		IRC_Connection *conn = KB_EstablishConnection ("ubq323.website");
		IRC_JoinChannelByName (conn, "b");
		IRC_JoinChannelByName (conn, "a");
	}
	{
		IRC_Connection *conn = KB_EstablishConnection ("localhost");
		IRC_JoinChannelByName (conn, "b");
	}
	
	_KB_C_Init ();
	
	size_t cid = 0;
	while (1) {
		cid = ++ cid % (KB_ConnectionsCnt + 1);
		IRC_Connection *conn = KB_Connections [cid];
		
		IRC_Message msg;
		
		if (IRC_GetMessage (conn, &msg) != NULL) {
		
			char *begin = strcasestr (msg.msg, "kit");
			
			if (begin != NULL) {
				begin += 3;
				char cmd [16] = { '\0' };
				bool cont = true;
				size_t i = 0;
				for (; cont; i ++) {
					switch (begin [i]) {
						case ' ': case '\0':
							cont = false;
						break;
						
						default:
							if (i == 15)
								cont = false;
							cmd [i] = begin [i];
						break;
					}
				}
				
				KB_CallCmd (cmd, begin + i, &msg);
			}
		}
		usleep (100);
	}
	
	return 0;
}
