#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int
main(void)
{
	if(open("tempfile", O_RDWR) < 0) {
		perror("open error");
	}

	if(unlink("tempfile") < 0) {
		perror("unlink error");
	}

	printf("file unlinked\n");
	sleep(15);
	printf("done\n");
	exit(0);
}
