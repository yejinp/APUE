#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/resource.h>

int
main()
{
	struct	rusage	ru;
	if(getrusage(RUSAGE_SELF, &ru) < 0) {
		perror("getrusage error");
		exit(9);
	}
	exit(0);
}
