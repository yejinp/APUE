#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>

extern void pr_exit(int );

int
main(void)
{
	pid_t	pid;
	int	status;

	if((pid = fork()) < 0) {
		perror("fork error");
		exit(9);
	} else if(pid == 0) {
		exit(7);
	}

	if(wait(&status) != pid) {
		perror("wait error");
		exit(7);
	}

	pr_exit(status);

	if((pid = fork()) < 0) {
		perror("fork error");
		exit(8);
	} else if(pid == 0)
		abort();

	if(wait(&status) != pid) {
		perror("wait error");
		exit(6);
	}
	pr_exit(status);

	if((pid = fork()) < 0) {
		perror("fork error");
		exit(9);
	} else if(pid == 0)
		status /= 0;

	if(wait(&status) != pid) {
		perror("wait error");
		exit(8);
	}

	pr_exit(status);

	exit(0);

}
