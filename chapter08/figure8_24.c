#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int
main(int argc, char *argv[])
{
	int	status;

	if(argc < 2) {
		perror("command-line argument required");
		exit(9);
	}

	if((status = system(argv[1])) < 0) {
		perror("system() error");
	}

	pr_exit(status);

	exit(0);
}
