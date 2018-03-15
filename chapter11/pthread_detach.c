#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

int main()
{
	int	err = 0;
	printf("equal:%d\n", pthread_equal(pthread_self(), pthread_self()));
	err = pthread_detach(pthread_self());

	if(err) {
		printf("pthread detach failed: %s\n", strerror(err));
	}
	
	err = pthread_join(pthread_self(), NULL);
	if(err)
		printf("pthread join failed:%s\n", strerror(err));

}
