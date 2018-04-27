#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define		BUFFSIZE	4096

int
main(void)
{
	int	n;
	char	buf[BUFFSIZE];
	while((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
		if(write(STDOUT_FILENO, buf, n) != n) {
			perror("write error");	
			exit(9);
		}
	}

	if(n < 0) {
		perror("read error");
		exit(8);
	}

	exit(0);
}
