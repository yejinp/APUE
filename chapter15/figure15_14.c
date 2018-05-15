#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

int
main(void)
{
	int	c;
	while((c = getchar()) != EOF) {
		if(isupper(c))
			c = tolower(c);
		if(putchar(c) == EOF) {
			perror("putchar error");
			exit(9);
		}
		if(c == '\n') 
			fflush(stdout);
	}

	exit(0);
}

