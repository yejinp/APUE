#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>

extern void pr_mask(const char *);

static	void	sig_int(int);


int
main(void)
{
	sigset_t	newmask, oldmask, waitmask;
	pr_mask("program start:");

	if(signal(SIGINT, sig_int) == SIG_ERR){
		perror("signal(SIGINT) error");
		exit(8);
	}

	sigemptyset(&waitmask);
	sigaddset(&waitmask, SIGUSR1);

	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);

	/* 
 * 	 * Block SIGINT and save current signal mask.	
 * 	 */

	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
		perror("SIG BLOCK error");
		exit(8);
	}

	/*
 * 	 * Critical region of code.
 * 	*/

	pr_mask("in the critical region: ");

	/*
 * 	 * Pause, allowing all signal except SIGUSR1
 * 	*/
	if(sigsuspend(&waitmask) != -1) {
		perror("sigsuspend error");
		exit(7);
	}

	pr_mask("after return from sigsuspend: ");

	/*
 * 	 * Reset signal mask which unclocks SIGINT.
 * 	*/

	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
		perror("SIG_SETMASK error");
		exit(6);
	}

	/*
 *	 * And continue processing ...
 * 	*/

	pr_mask("program exit:");
	exit(0);
}

static void
sig_int(int signo)
{
	pr_mask("\nin sig_int: ");
}
