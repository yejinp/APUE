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

