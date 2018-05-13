#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

int
main(int argc, char **argv)
{
	int	fd;
	pid_t	pid;
	char	buf[5];
	struct	stat	statbuf;

	if(argc != 2) {
		fprintf(stderr, "usage:%s filename\n", argv[0]);
		exit(1);
	}

	if((fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) < 0) {
		perror("open error");
		exit(9);
	}

	if(write(fd, "abcdef", 6) != 6) {
		perror("write error");
		exit(9);
	}

	if(fstat(fd, &statbuf) < 0) {
		perror("fstat error");
		exit(9);
	}

	if(fchmod(fd, (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0) {
		perror("fchmod error");
		exit(9);
	}

	TELL_WAIT();

	if((pid = fork()) < 0) {
		perror("fork error");
		exit(9);
	} else if(pid > 0) {
		if(write_lock(fd, 0, SEEK_SET, 0) < 0) {
			perror("write_lock error");
			exit(9);
		}
		TELL_CHILD(pid);
		if(waitpid(pid, NULL, 0) < ) {
			perror("waitpid error");
			exit(9);
		}
	} else {
		WAIT_PARENT();

		set_fl(fd, O_NONBLOCK);

		if(read_lock(fd, 0, SEEK_SET, 0) != -1) {
			printf("child: read_lock succeeded\n");
			printf("read_lock of already-lockng region return %d\n", errno);

			if(lseek(fd, 0, SEEK_SET) == -1){
				perror("lseeek error");
				exit(9);
			}

			if(read(fd, buf, 2) < 0) {
				perror("read failed (mandatory locking works)\n");
				exit(9);
			} else {
				printf("read OK (no mandatory locking), buf = %2.2s\n", buf);
			}
		}
	}
	exit(0);
}
