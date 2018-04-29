#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
	FILE *ifp  = NULL;
	int i;
	char c;
	char s[1024] = {0};

	if(argc != 2) {
		printf("usage: %s <file_path>\n", argv[0]);
		exit(9);
	}

	ifp = fopen(argv[1], "r");
	if(ifp == NULL) {
		perror("fopen failed");
		exit(8);
	}

	if(1 != fscanf(ifp,"%[^,]s\n", s)) {
		printf("file format error.\n");

	} else {
		printf("s = %s\n", s);
	}

#if 0
	if(1 != fscanf(ifp, "%d\n\n", &i)) {
		printf("file format error.\n");
	}

#endif
	printf("i = %d\n", i);
	exit(0);
}
