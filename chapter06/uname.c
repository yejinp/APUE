#include <sys/utsname.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int
main()
{
	struct	utsname	uts;

	if(uname(&uts) < 0) {
		perror("uname error");
		exit(9);
	}
	printf("sysname : %s\n", uts.sysname);
	printf("nodename: %s\n", uts.nodename);
	printf("release : %s\n", uts.release);
	printf("version : %s\n", uts.version);
	printf("machine : %s\n", uts.machine);

	exit(0);
}
