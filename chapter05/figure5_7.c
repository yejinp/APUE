#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
	int i = 89, j = -98;
	float	f = 9.99879;

	printf("%*.*f\n", 3, 2, f);

	printf("%-d\n", j);
	printf("%+d\n", j);
	printf("% d\n", j);
	printf("%#x\n", j);
	printf("%0x\n", j);

	printf("%-d\n", i);
	printf("%*d\n", 5 , i);
	printf("%+d\n", i);
	printf("% d\n", i);
	printf("%#x\n", i);
	printf("%0x\n", i);
	exit(0);
}
