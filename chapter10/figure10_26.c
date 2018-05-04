#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static void
sig_int(int signo)
{
	printf("caught SIGINT\n");
}

sig_chld(int signo) 
{
	printf("caught SIGCHLD\n");
}

int
main(void)
{
	if(signal(SIGINT, sig_int) == SIG_ERR) {
		perror("signal(SIGINT) error");
		exit(9);
	}
	if(signal(SIGCHLD, sig_int) == SIG_ERR) {
		perror("signal(SIGCHLD) error");
		exit(9);
	}
	if(system("/usr/bin/ed") < 0) {
		perror("system (0 error");
		exit(8);
	}
	exit(0);
}
