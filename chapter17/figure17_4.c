#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define		MAXLINE	1024
static void sig_pipe(int);

int
main(void)
{
	int 	n;
	int 	fd[2];
	pid_t	pid;
	char	line[MAXLINE];
	
	if(signal(SIGPIPE, sig_pipe) == SIG_ERR) {
		perror("signal error");
		exit(9);
	}

	if(s_pipe(fd) < 0) {
		perror("pipe error");
		exit(8);
	}

	if((pid = fork()) < 0) {
		perror("fork error");
		exit(7);
	} else	if(pid > 0) {
		close(fd[1]);

		while(fgets(line, MAXLINE, stdin) != NULL) {
			n = strlen(line);
			if(write(fd[0], line, n) != n) {
				perror("write error to pipe");
				exit(8);
			}

			if((n = read(fd[0], line, MAXLINE)) < 0) {
				perror("read error from pipe");
				exit(7);
			}

			if(n == 0) {
				printf("child closed pipe.\n");
				break;
			}

			line[n] = 0;

			if(fputs(line, stdout) == EOF) {
				perror("fputs error");
				exit(6);
			}
		}
		if(ferror(stdin)) {
			perror("fgets error on stdin");
			exit(9);
		}
		exit(0);

	} else {

		close(fd[0]);
		if(fd[1] != STDIN_FILENO &&
		  dup2(fd[1], STDIN_FILENO) != STDIN_FILENO) {
			perror("dup2 error to stdin");
			exit(5);
		}

		if(fd[1] != STDOUT_FILENO &&
		  dup2(fd[1], STDOUT_FILENO) != STDOUT_FILENO) {
			perror("dup2 error to stdin");
			exit(5);
		
		}

		if(execl("./add2", "add2", (char *)0) < 0 ) {
			perror("execl error");
		}
	} 
	exit(0);
}

static void sig_pipe(int signo) 
{
	printf("SIGPIPE caught\n");
	exit(1);
}

