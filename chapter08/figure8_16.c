#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>

char	*env_init[] = {"USER=unknown", "PATH=/tmp", NULL};

int
main(void)
{
	pid_t	pid;
	
	if((pid = fork()) < 0) {
		perror("fork error");
		exit(9);
	} else if (pid == 0) {
		if(execle("/home/yejp/bin/echoall", "echoall", "myarg1", "MY ARG2", (char *)0, env_init) < 0) {
			perror("execle error");
			exit(8);
		}
	}

	if(waitpid(pid, NULL, 0) < 0) {
		perror("waitpid error");
		exit(9);
	}

	if((pid = fork()) < 0) {
		perror("fork error");
		exit(9);
	} else if(pid == 0) {
		if(execlp("echoall", "echoall", "only 1 arg", (char*)0) < 0) {
			perror("execlp error");
			exit(8);
		}
	}

	exit(0);
}

