#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

volatile sig_atomic_t	quitflag;  /* set nozero by signal handler */

static void
sig_int(int signo) /* one signal handler for SIGINT and SIGQUIT */
{
	if(signo == SIGINT) {
		printf("\ninterrupt\n");
	} else if(signo == SIGQUIT)
		quitflag = 1; /* set flag for main loop */
}

int main(void)
{
	sigset_t	newmask, oldmask, zeromask;

	if(signal(SIGINT, sig_int) == SIG_ERR) {
		perror("signal(SIGINT) error");
		exit(9);
	}
	if(signal(SIGQUIT, sig_int) == SIG_ERR) {
		perror("signal(SIGQUIT) error");
		exit(9);
	}

	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);

	/*
 *	Block SIGQUIT and save current signal mask.
 * 	*/

	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
		perror("SIG_BLOCK error");
		exit(9);
	}

	while(quitflag == 0) {
		sigsuspend(&zeromask);
	}

	/*
 *	 * Reset signal mask which unclokcs SIGQUIT.
 * 	*/
	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
		perror("SIG_SETMASK error");
		exit(9);
	}

	exit(0);
}
