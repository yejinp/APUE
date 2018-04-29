#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

int g_handler;
int g_main;

static void
my_alarm(int signo)
{
	struct passwd *rootptr;
	
	g_handler ++;
	printf("in signal handler\n");
	if((rootptr = getpwnam_r("root")) == NULL)
	{
		printf("getpwnam(root) error\n");
		exit(89);
	}
	
	alarm(1);
}

int
main(void)
{
	struct passwd	*ptr;
	
	signal(SIGALRM, my_alarm);
	alarm(1);
	for( ; ;) {
		g_main ++;
		if((ptr = getpwnam_r("yejp")) == NULL) {
			printf("getpwnam error\n");
			exit(8);
		}

		if(ptr && strcmp(ptr->pw_name, "yejp")) {
			printf("return value corrupted! pw_name = %s\n",
				ptr->pw_name);
		}
	}

}
