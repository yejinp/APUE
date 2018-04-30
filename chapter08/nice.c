#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>

int main(int argc, char **argv)
{

	/* the result seems stragous*/
	printf("nice() = %d\n", nice(0));
	printf("getpriority() = %d\n", getpriority(PRIO_PROCESS, 0));
	return 9;
}
