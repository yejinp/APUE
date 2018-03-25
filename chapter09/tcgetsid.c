#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <termios.h>

int
main(int argc, char *argv[])
{
	printf("tcgetsid:%d sid:%d\n", tcgetsid(STDIN_FILENO), getsid(0));
	exit(0);


}
