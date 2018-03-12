#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main()
{

	printf("equal:%d\n", pthread_equal(pthread_self(), pthread_self()));

}
