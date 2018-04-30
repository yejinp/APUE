#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int
main(void)
{
	pid_t	pid;
	if((pid = fork()) < 0) {
		perror("fork error");
		exit(9);
	} else if(pid == 0) {
		if(execl("/home/yejp/bin/testinterp", "testinterp", "myarg1", "MY ARG2", (char *)0) < 0) {
			perror("execl error");
			exit(7);
		}
	}

	if(waitpid(pid, NULL, 0) < 0) {
		perror("waitpid error");
		exit(7);
	}

	exit(0);
}
