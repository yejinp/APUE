#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main(void)
{
	printf("equal:%d\n", pthread_equal(pthread_self(), pthread_self()));
	exit(0);
}
