#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	printf("user id:%d\ngroup id:%d\neffective user id:%d\neffective group id:%d\n", getuid(), getgid(), geteuid(), getegid());
	if(0 > open("./test_mod", O_CREAT))
		perror("open error");

}
