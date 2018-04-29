#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int
main(void)
{
	printf("pwd = %s\n", getcwd(NULL, 0));

	if(chdir("/tmp") < 0) {
		perror("chdir failed");
		exit(9);
	}

	printf("chdir to /tmp succeeded\n");
	exit(0);
}
