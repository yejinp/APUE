#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

static void *test_thd(void *argv)
{
	printf("in the thread.\n");
}


int make_detached_thread(void *(*fn)(void*), void *arg)
{

	int	err;
	pthread_t	tid;
	pthread_attr_t	attr;

	err = pthread_attr_init(&attr);
	if(err != 0) {
		return (err);
	}

	err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if(err == 0) {
		err = pthread_create(&tid, &attr, fn, arg);
	}

	pthread_attr_destroy(&attr);
	return (err);
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

	make_detached_thread(test_thd, NULL);

	exit(0);
}
