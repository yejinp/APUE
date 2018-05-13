#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/*
 * test the default cancel stat
 */
int
main(void)
{
	int	oldstat, stat= 0;
	
	if(0 == pthread_setcancelstate(stat, &oldstat)) {
		printf("default cancel stat is: %s\n", oldstat==PTHREAD_CANCEL_ENABLE?"enable":"disable");
	}

	exit(0);
}
