#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t	lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t	lock2 = PTHREAD_MUTEX_INITIALIZER;

void
prepare(void)
{
	printf("preparing locks ...\n");
	pthread_mutex_lock(&lock1);
	pthread_mutex_lock(&lock2);
}

void parent(void)
{
	printf("parent unlocking locks ...\n");
	pthread_mutex_unlock(&lock1);
	pthread_mutex_unlock(&lock2);
}
void child(void)
{
	printf("child unlocking locks ...\n");
	pthread_mutex_unlock(&lock1);
	pthread_mutex_unlock(&lock2);
}

void *
thr_fn(void *arg)
{

	printf("thread started ...\n");
	pause();
	return 0;
}

int
main(void)
{
	int	err;
	pid_t	pid;
	pthread_t	tid;
#if defined(BSD) || defined(MACOS)
	printf("pthread_atfork is unsupported\n");
#else
	if((err = pthread_atfork(prepare, parent, child)) != 0)
	{
		printf("can't install fork handlers\n");
		exit(err);
	}
	err = pthread_create(&tid, NULL, thr_fn, 0);
	if(err) {
		printf("cann't create thread\n");
		exit(err);
	}
	sleep(2);
	printf("parent about to fork ...\n");

	if((pid = fork()) < 0) {
		printf("fork failed\n");
		exit(8);
	} else if(pid == 0) {
		printf("child returned from fork\n");
	} else {
		printf("parent returned from fork\n");
	}
#endif
	exit(0);

}
