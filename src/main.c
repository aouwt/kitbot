#define _GNU_SOURCE

#include <irc.h>
#include <kb.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>


int main (void) {
	IRC_Connection *conn = IRC_NewConnection (NULL, "ubq323.website", 0, "kitbot");
	IRC_SetNick (conn, "kitbot");
	
	IRC_JoinChannelByName (conn, "b");
	IRC_JoinChannelByName (conn, "a");
	
	_KB_C_Init ();
	
	while (1) {
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
