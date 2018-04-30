#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

int
main(void)
{
	pid_t	pid;

	if((pid = fork()) < 0) {
		perror("fork error");
	} else if(pid) {
		sleep(2);
		exit(2);
	}

	if((pid = fork()) < 0) {
		perror("fork error");
	} else if(pid) {
		sleep(4);
		abort();
	}

	if((pid = fork()) < 0) {
		perror("fork error");
	} else if(pid) {
		execl("bin/dd", "dd", "if=/etc/termcap", "of=/dev/null", NULL);
		exit(7);
	}

	if((pid = fork()) < 0) {
		perror("fork error");
	} else if(pid) {
		sleep(8);
		exit(0);
	}

	sleep(6);
	kill(getpid(), SIGKILL);
	exit(6);
}
