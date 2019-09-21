#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/resource.h>

#define PRINT_USAGE(prs,USAGE)    printf("%s:%ld\n", USAGE, prs->ru_#USAGE)


void print_rusage(struct rusage *prs)
{
	if(prs == NULL)
	{
		return;
	}

	printf("ru_maxrss:%ld\n", prs->ru_maxrss);
	printf("ru_nswap:%ld\n", prs->ru_nswap);
	printf("ru_inblock:%ld\n", prs->ru_inblock);
	printf("ru_oublock:%ld\n", prs->ru_oublock);
	printf("ru_minflt:%ld\n", prs->ru_minflt);
	printf("ru_majflt:%ld\n", prs->ru_majflt);
	printf("ru_msgsnd:%ld\n", prs->ru_msgsnd);
	printf("ru_msgrcv:%ld\n", prs->ru_msgrcv);
	printf("ru_nsignals:%ld\n", prs->ru_nsignals);
	printf("ru_nvcsw:%ld\n", prs->ru_nvcsw);
	printf("ru_nivcsw:%ld\n", prs->ru_nivcsw);
}

int
main(int argc, char *argv[])
{

	int	ret;
	struct rusage rs = {0};
	
	ret = getrusage(RUSAGE_SELF, &rs);
	printf("getrusage ret=%d\n", ret);
	print_rusage(&rs);
	
}
