#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int 
main(int argc, char *argv[])
{
	printf("pid:%d  ppid:%d  pgid:%d pgrp:%d\n", 
		getpid(), getppid(), getpgid(0), getpgrp());
	exit(0);
}
