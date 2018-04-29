#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define		MAXLEN	1024

int
main(void)
{
	char	name[L_tmpnam], line[MAXLEN];
	FILE	*fp;
	printf("%s\n", tmpnam(NULL));

	tmpnam(name);

	printf("%s\n", name);
	if((fp = tmpfile()) == NULL) {
		printf("tmpfile error\n");
		exit(9);
	}

	fputs("one line of output\n", fp);
	rewind(fp);

	if(fgets(line, sizeof(line), fp) == NULL) {
		printf("fgets error\n");
	}

	fputs(line, stdout);
	exit(0);
}
