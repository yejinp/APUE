#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

static void *test_thd(void *argv)
{
	printf("in the thread.\n");
}

int main()
{

	pthread_t	tid;
	pthread_attr_t	attr;

	printf("in the main thread.\n");
	if(pthread_attr_init(&attr) != 0)
	{
		printf("attr init failed.\n");
		exit(1);
	}

	if(pthread_create(&tid, &attr, &test_thd, NULL) != 0)
	{
		printf("thread create error");
		exit(2);
	}

	exit(0);
}
