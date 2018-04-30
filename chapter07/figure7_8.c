#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

int
main(int argc, char *argv[])
{
	char *p ;
	if(argc != 2) {
		printf("Usage: %s <env[=val]>\n", argv[0]);
		exit(9);
	}
	
	if((p = strstr(argv[1], "=")) == NULL) {
		if(getenv(argv[1])) {
			printf("%s=%s\n", argv[1], getenv(argv[1]));
		}
	} else {
		*p = 0;
		if(setenv(argv[1], p+1, 0) == 0) {
			printf("%s=%s\n", argv[1], getenv(argv[1]));
		}
#if 1
		/* putenv(argv[1]) return 0, but genenv the value of the variable failed ?? */
		//if(putenv(argv[1]) == 0) {
		if(putenv("A=abc") == 0) {
			printf("%s=%s\n", "A", getenv("A"));
		}

#endif
	}

	exit(0);
}
