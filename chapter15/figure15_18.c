#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#define		MAXLINE		1024

static void sig_pipe(int);

int
main(void)
{
	int	n, fd1[2], fd2[2];
	pid_t	pid;
	char	line[MAXLINE];

	if(signal(SIGPIPE, sig_pipe) == SIG_ERR) {
		perror("signal error");
		exit(9);
	}

	if(pipe(fd1) < 0 || pipe(fd2) < 0){
		perror("pipe error");
		exit(9);
	}

	if((pid = fork()) < 0) {
		perror("fork error");
		exit(9);
	} else if(pid > 0) {
		close(fd1[0]);
		close(fd2[1]);

		while(fgets(line, MAXLINE, stdin) != NULL) {
			n = strlen(line);
			if(write(fd1[1], line, n) != n) {
				perror("write error");
				exit(8);
			}
			if((n = read(fd2[0], line, MAXLINE)) < 0) {
				perror("read error from pipe");
				exit(8);
			}
			
			if(n == 0) {
				printf("child closed pipe");
				break;
			}
			line[n] = 0;
			if(fputs(line, stdout) == EOF) {
				perror("fputs error");
				exit(8);
			}
		}
		if(ferror(stdin)) {
			printf("fgets error on stdin\n");
			exit(9);
		}
	} else {
		close(fd1[1]);
		close(fd2[0]);
		if(fd1[0] != STDIN_FILENO) {
			if(dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO) {
				perror("dup2 error");
				exit(9);
			}
			close(fd1[1]);
		}
		if(fd2[1] != STDOUT_FILENO) {
			if(dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO) {
				perror("dup2 error");
				exit(9);
			}
			close(fd2[0]);
		}

		if(execl("./figure15_17", "./figure15_17", (char *) 0) < 0) {
			perror("execl error");
			exit(9);
		}
	}
	exit(0);
}

static void
sig_pipe(int signo)
{
	printf("SIGPIPE caught\n");
	exit(1);
}
