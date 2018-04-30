#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int
main(int argc, char *argv[])
{

	printf("getlogin() = %s\n", getlogin());
	exit(0);
}
