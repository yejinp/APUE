#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <signal.h>

#define		MAXLINE 1024

static void sig_alrm(int);

int
main(void)
{
	int	n;
	char	line[MAXLINE];
	
	if(signal(SIGALRM, sig_alrm) == SIG_ERR) {
		perror("signal(SIGALRM) error.\n");
		exit(8);
	}

	alarm(10);
	if((n = read(STDIN_FILENO, line, MAXLINE)) < 0) {
		perror("read error");
		exit(9);
	}

	alarm(0);

	write(STDOUT_FILENO, line, n);
	exit(0);
}

static void
sig_alrm(int signo)
{
	/* do nothing.  */
}
