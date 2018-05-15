#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define		PAGER	"${PAGER:-more}"
#define		MAXLINE		1024
int
main(int argc, char *argv[])
{

	char	line[MAXLINE];
	FILE	*fpin, *fpout;

	if(argc != 2) {
		printf("usage: %s <pathname>\n", argv[0]);
		exit(9);
	}

	if((fpin = fopen(argv[1], "r")) == NULL) {
		printf("can't open %s\n", argv[1]);
		exit(9);
	}

	if((fpout = popen(PAGER, "w")) == NULL) {
		perror("poepn error");
		exit(9);
	}

	while(fgets(line, MAXLINE, fpin) != NULL) {
		if(fputs(line, fpout) == EOF) {
			perror("fputs error to pipe");
			exit(9);
		}
	}

	if(ferror(fpin)) {
		printf("fgets error\n");
		exit(8);
	}

	if(pclose(fpout) == -1) {
		perror("pclose error");
		exit(8);
	}
	exit(0);
}
