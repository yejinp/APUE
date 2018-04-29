#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	mode_t	mode = umask(0);;
	printf("user id:%d\ngroup id:%d\neffective user id:%d\neffective group id:%d\n", getuid(), getgid(), geteuid(), getegid());
	printf("umask:0x%x\n", mode);
	umask(mode);
	/* fuck! what happend to this file */
	if(0 > open("./test_mod", O_CREAT))
		perror("open error");

}
