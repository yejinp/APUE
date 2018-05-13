#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

static void
lockabyte(const char *name, int fd, off_t offset)
{
	if(writew_lock(fd, offset, SEEK_SET, 1) < 0){
		printf("%s: writew_lock error\n", name);
		return;
	}
	printf("%s: got the lock, byte %ld\n", name, offset);
	return;
}

int
main(void)
{
	int	fd;
	pid_t	pid;

	if((fd = creat("templock", FILE_MODE)) < 0) {
		printf("create error\n");
	}

	if(write(fd, "ab", 2) != 2) {
		printf("write error\n");
	}

	TELL_WAIT();
	if((pid = fork()) < 0) {
		printf("fork error\n");
	} else if(pid == 0) {
		lockabyte("child", fd, 0);
		TELL_PARENT(getppid());
		WAIT_PARENT();
		lockabyte("child", fd, 1);
	} else {
		lockabyte("parent", fd, 0);
		TELL_CHLD(pid);
		WAIT_CHLD();
		lockabyte("parent", fd, 1);
	}
	exit(0);
}

