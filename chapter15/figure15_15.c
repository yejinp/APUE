#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define		MAXLINE  1024
int
main(void)
{
	char	line[MAXLINE];
	FILE	*fpin;

	if((fpin = popen("./figure15_14", "r")) == NULL) {
		perror("popen error");
		exit(8);
	}

	for( ; ; ) {
		fputs("prompt> ", stdout);
		fflush(stdout);
		if(fgets(line, MAXLINE, fpin) == NULL) {
			break;
		}
		if(fputs(line, stdout) == EOF) {
			perror("fputs error to pipe");
			exit(8);
		}
	}

	if(pclose(fpin) == -1) {
		perror("pclose error");
		exit(8);
	}

	putchar('\n');
	exit(0);
}
