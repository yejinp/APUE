#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int 
main(void)
{
	char	ptr[1024] = {0};
	int	size = 1024;
	
	if(chdir("/usr/spool/uucppublic") < 0) {
		perror("chdir failed");
	}

	if(getcwd(ptr, size) == NULL) {
		perror("getcwd failed");
	}

	printf("cwd = %s\n", ptr);
	exit(0);
}
