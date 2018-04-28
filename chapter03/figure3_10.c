#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
	int	val;

	if(argc != 2) {
		printf("usage: %s <descriptor#>\n", argv[0]);
		exit(9);
	}

	if((val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0) {
		printf("fcntl erro for fd %d", atoi(argv[1]));
		exit(8);
	}

	switch(val & O_ACCMODE) {
	case O_RDONLY:
		printf("read only\n");
		break;
	case O_WRONLY:
		printf("write only");
		break;
	case O_RDWR:
		printf("read write");
		break;
	default:
		printf("unkown access mode\n");
	}

	if(val & O_APPEND) 
		printf(", append");

	if(val & O_NONBLOCK) 
		printf(", nonblocking");

#if defined(O_SYNC)
	if(val & O_SYNC)
		printf(", synchronous writes");
#endif
#if !defined(_POSIX_C_SOURCE) && defined (O_FSYNC)
	if(val & O_FSYNC)
		printf(", synchronous writes");
#endif

	putchar('\n');
	exit(0);

}
