#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	glob = 6;
char	buf[] = "a write to stdout\n";

int
main(void) 
{
	int	var;
	pid_t 	pid;

	var = 88;
	if(write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1) {
		perror("write error");
		exit(9);
	}

	printf("before fork\n");

	if((pid = vfork()) < 0) {
		perror("fork error");
		exit(8);
	} else if(pid == 0) {
		glob++;
		var++;
		_exit(0);
	}

	printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
	exit(0);
}
