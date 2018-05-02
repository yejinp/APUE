#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <setjmp.h>

#define		MAXLINE 1024

static void sig_alrm(int);
static jmp_buf	env_alrm;

int
main(void)
{
	int	n;
	char	line[MAXLINE];
	
	if(signal(SIGALRM, sig_alrm) == SIG_ERR) {
		perror("signal(SIGALRM) error");
		exit(8);
	}
	if(setjmp(env_alrm) != 0) {
		printf("read timeout\n");
		exit(9);
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
	printf("received signo:%d\n", signo);
	longjmp(env_alrm, 2);
}
