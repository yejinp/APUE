#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

#define		DEF_PAGER	"/bin/more"
#define		MAXLINE		1024
int
main(int argc, char *argv[])
{
	int	n;
	int	fd[2];
	pid_t	pid;
	char	*pager, *argv0;
	char	line[MAXLINE];
	FILE	*fp;

	if(argc != 2) {
		printf("usage: %s <pathname>\n", argv[0]);
		exit(9);
	}

	if((fp = fopen(argv[1], "r")) == NULL) {
		printf("can't open %s\n", argv[1]);
		exit(9);
	}

	if(pipe(fd) < 0) {
		perror("pipe error");
		exit(9);
	}

	if((pid = fork()) < 0) {
		printf("fork error");
		exit(9);
	} else if(pid > 0) {
		close(fd[0]);
		while(fgets(line, MAXLINE, fp) != NULL) {
			n = strlen(line);
			if(write(fd[1], line, n) != n) {
				perror("write to pipe error");
				exit(9);
			}
		}

		if(ferror(fp)) {
			printf("fgets error");
			exit(9);
		}

		close(fd[1]);

		if(waitpid(pid, NULL, 0) < 0) {
			perror("waitpid error");
			exit(9);
		}
		exit(0);
	} else {
		close(fd[1]);
		if(fd[0] != STDIN_FILENO) {
			if(dup2(fd[0], STDIN_FILENO) != STDIN_FILENO) {
				perror("dup2 error to stdin");
				exit(9);
			}

			close(fd[0]);
		}

		if((pager = getenv("PAGER")) == NULL) {
			pager = DEF_PAGER;
		}

		if((argv0 = strrchr(pager, '/')) != NULL) {
			argv0 ++;
		} else {
			argv0 = pager;
		}

		if(execl(pager, argv0, (char *)0) < 0) {
			printf("execl error for %s\n", pager);
		}
		exit(0);
	}
}
