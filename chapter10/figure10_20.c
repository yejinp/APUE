#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

extern void pr_mask(const char *);

static void sig_usr1(int);
static void sig_alrm(int);
static sigjmp_buf	jmpbuf;
static volatile sig_atomic_t	canjmp;

int
main(void)
{
	if(signal(SIGUSR1, sig_usr1) == SIG_ERR) {
		perror("signal(SIGUSR1) error");
		exit(9);
	}
	if(signal(SIGALRM, sig_alrm) == SIG_ERR) {
		perror("signal(SIGALRM) error");
		exit(9);
	}

	pr_mask("starting main:"); /* Figure 10.14 */

	if(sigsetjmp(jmpbuf, 1)) {
		pr_mask("ending main:");
		exit(0);
	}

	canjmp = 1; /* now sigsetjmp() is OK */

	for( ; ; ) 
		pause();
}

static void
sig_usr1(int signo)
{
	time_t	starttime;
	if(canjmp == 0) 
		return ; /* unexpected signal, ignore */

	pr_mask("starting sig_usr1:");

	alarm(3);  /* SIGALRM IN 3 SECONDS */
	starttime = time(NULL);

	for( ; ; ) /* busy wait for 5 seconds */
		if(time(NULL) > starttime + 5)
			break;

	pr_mask("finishing sig_usr1:");
	canjmp = 0;
	siglongjmp(jmpbuf, 1); /* jump back to main, don't return */
}

static void
sig_alrm(int	signo)
{
	pr_mask("in sig_alrm: ");
}
