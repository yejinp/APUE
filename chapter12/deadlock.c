#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int
main(void)
{
	pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	pthread_mutex_lock(&mutex); /*deallock when it try to get a locked lock */
	exit(0);
}
