#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

static void sig_int(int);

#define		MAXLINE	512
int main()
{
	char	buf[MAXLINE];
	pid_t	pid;
	int	status;

	if(signal(SIGINT, sig_int) == SIG_ERR) {
		perror("signal error");
		exit(9);
	}

	printf("%% ");
	while(fgets(buf, MAXLINE, stdin) != NULL) {
		if(buf[strlen(buf) - 1] =='\n')
			buf[strlen(buf) - 1] = 0;

		if((pid = fork()) < 0) {
			perror("fork error");
		} else if(pid == 0) {
			execlp(buf, buf, (char *)0);
			printf("couldn't execute: %s", buf);
			exit(127);
		}

		if((pid == waitpid(pid, &status, 0)) < 0)
			perror("waitpid error");
		printf("%% ");
	}

}

void
sig_int(int signo)
{
	printf("interrupt\n%%");
}
