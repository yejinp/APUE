#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

int
main(int argc, char *argv[]) 
{
	if(argc != 2) {
		printf("usage: %s <pathname>\n", argv[0]);
		exit(9);
	}

	if(access(argv[1], R_OK) < 0) {
		perror("access error");
	} else {
		printf("read access OK\n");
	}

	
	if(open(argv[1], O_RDONLY) < 0) {
		perror("open file error");
	} else {
		printf("open for reading OK\n");
	}

	exit(0);
}
