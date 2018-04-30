#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int 
main(int argc, char *argv[])
{
	printf("sid:%d\n", getsid(0));
	if(setsid() < 0) {
		perror("set sid failed");
	} else {
		printf("set sid ok.\n");
		printf("after set. pid:%d sid:%d\n", getpid(), getsid(0));
	}
		
	exit(0);
}
