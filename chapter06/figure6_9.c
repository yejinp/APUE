#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

int
main(void)
{
	time_t	tt;
	struct	timeval	tv;
	struct	tm	*ptm = NULL;

	char tb[256] = {0}, *pc1 = NULL, *pc2 = NULL;

	printf("time = %ld\n", time(&tt));
	gettimeofday(&tv, NULL);
	printf("time = %ld\n", tv.tv_sec);

	ptm = gmtime(&tt);
	localtime(&tt);

	/* attention the return of newline */
	printf("asctime = %s", asctime(ptm));
	pc1 = ctime(&tt);
	printf("ctime = %s", pc1);

	if(strftime(tb, 256, "%c", ptm)) {
	/* attention the return of newline */
		printf("formatted time = %s\n", tb);
	}


	/* check if the return pointer of ctime stored in static ? */
	sleep(3);
	printf("time = %ld\n", time(&tt));
	pc2 = ctime(&tt);
	printf("ctime = %s", pc1);
	printf("ctime = %s", pc2);
	if(pc1 == pc2) {
		printf("stored in static array.\n");
	}
	
	exit(0);
}
