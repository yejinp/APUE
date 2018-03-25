#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int 
main(int argc, char *argv[])
{
	printf("pid:%d  ppid:%d  pgrp:%d\n", getpid(), getppid(), getpgrp());
	exit(0);
}
