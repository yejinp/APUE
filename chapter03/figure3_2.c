#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define  FILE_MODE  1


char	buf1[] = "abcdefghij";
char	buf2[] = "ABCDEFGHIJ";

int
main(void)
{
	int	fd;
	if((fd = creat("file.hole", FILE_MODE)) < 0) {
		perror("create error");
		exit(8);
	}

	if(write(fd, buf1, 10) != 10) {
		perror("buf1 write error");
		exit(8);
	}

	if(lseek(fd, 16384, SEEK_SET) == -1) {
		perror("lseek error");
		exit(7);
	}

	if(write(fd, buf2, 10) != 10) {
		perror("buf2 write error");
		exit(8);
	}

	exit(0);
}
