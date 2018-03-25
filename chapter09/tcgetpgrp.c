#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

void getpgrp_print()
{
	pid_t pgrp;
	if((pgrp = tcgetpgrp(STDIN_FILENO)) < 0) {
		perror("get pgrp failed");
	} else {
		printf("pgrp:%d\n", pgrp);
	}
}


int 
main(int argc, char *argv[])
{

	getpgrp_print();
	printf("sid:%d\n", getsid(0));
	if(setsid() < 0) {
		perror("set sid faile");
	} else {
		getpgrp_print();
		printf("set sid ok.\n");
		printf("after set. pid:%d sid:%d\n", getpid(), getsid(0));
	}
		
	exit(0);
}
