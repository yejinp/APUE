#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	printf("Hello world for process ID %d\n", getpid());
	exit(0);
}
