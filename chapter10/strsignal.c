#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

int main(int argc, char *argv[])
{

	if(argc == 2) {
		printf("string of signal number %d is %s\n", atoi(argv[1]), strsignal(atoi(argv[1])));
		psignal(atoi(argv[1]), "Attention Signal");
	}

}
