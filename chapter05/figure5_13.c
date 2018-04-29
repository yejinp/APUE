#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
	if(argc != 3) {
		printf("usage:%s <dir> <prefix>\n", argv[0]);
		exit(9);
	}

	printf("%s\n", tempnam(argv[1][0]!= ' ' ? argv[1] : NULL, argv[2][0] != ' ' ? argv[2] : NULL));

	exit(0);
}
