#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define		MAXLINE 	1024
int
main(void)
{
	int	int1, int2;
	char	line[MAXLINE];

	if(setvbuf(stdin, NULL, _IOLBF, 0) != 0) {
		perror("setvbuf error");
		exit(9);
	}
	if(setvbuf(stdout, NULL, _IOLBF, 0) != 0) {
		perror("setvbuf error");
		exit(9);
	}
	
	while(fgets(line, MAXLINE, stdin) != NULL ) {
		if(sscanf(line, "%d%d", &int1, &int2) == 2){
			if(printf("%d\n", int1 + int2) == EOF) {
				printf("printf error\n");
				exit(9);
			}
		} else {
			if(printf("invalid args\n") == EOF) {
				printf("printf error\n");
				exit(9);
			}
		}
	}

	exit(0);
}
