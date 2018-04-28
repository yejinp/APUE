#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int
main(void)
{
	int	fd1, fd2;

	if( (fd1 = dup(STDIN_FILENO)) < 0) {
		perror("dup error");
		exit(9);
	}

	printf("fd1 = %d\n", fd1);

	if(( fd2 = dup2(STDOUT_FILENO, STDOUT_FILENO)) < 0) {
		perror("dup2 error");
		exit(9);
	
	}
	printf("fd2 = %d\n", fd2);
}
