#include <stdio.h>
#include <stdlib.h>

static void my_exit1(void);
static void my_exit2(void);

int
main(void)
{
	if(atexit(my_exit2)) {
		perror("can't register myexit2");
		exit(9);
	}

	if(atexit(my_exit1)) {
		perror("can't register myexit1");
		exit(9);
	}

	if(atexit(my_exit1)) {
		perror("can't register myexit1");
		exit(9);
	}

	printf("main is done\n");
	return (0);
}

static void
my_exit1()
{
	printf("first exit handler\n");
}

static void
my_exit2()
{
	printf("second exit handler\n");
}
