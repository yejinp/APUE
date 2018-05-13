#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static void *test_thd(void *argv)
{
	int err;
	printf("in the thread.\n");
	printf("concurrency:%d\n", pthread_getconcurrency());
	err = pthread_setconcurrency(3);
	if(err) {
		printf("set concurrency to 3 error.\n");
	} else {
		printf("set concurrency to 3 ok.\n");
	}
	
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
	sleep(5);
	exit(0);
}
