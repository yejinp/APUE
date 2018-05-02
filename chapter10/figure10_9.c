#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <setjmp.h>

static void sig_int(int);
extern int sleep2(int);

int main()
{
	unsigned int unslept;
	if(signal(SIGINT, sig_int) == SIG_ERR) {
		printf("signal(SIGINT) err");
		exit(4);	
	}

	unslept = sleep2(5);
	printf("sleep2 returned: %u\n", unslept);
	exit(0);
}


static void 
sig_int(int signo)
{
	int 	i, j;
	volatile	int k;

	printf("\n sig_int starting\n");
	/* Attention: Turn these loops to run for more than 5 seconds 
	 * on whatever system this test program is run
	 */

	for(i = 0; i < 300000; i++)
		for(j = 0; j < 400000; j++)
			k += j * i;

	printf("sig_int finished\n");

}
