#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
	int i = 980;
	char c = 98;
	float f = 7.876;
	long long l = 898983;

	printf("%hhd\n", c);
	printf("%Ld\n", l);

	exit(0);
}
