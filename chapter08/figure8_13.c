#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

static void charatatime(char *);

int
main(void)
{
	pid_t	pid;

	TELL_WAIT();
	
	if((pid = fork()) < 0) {
		perror("fork error");
		exit(9);
	} else if(pid == 0) {
		WAIT_PARENT();
		charatatime("output from child\n");
	} else {
		charatatime("output from parent\n");
		TELL_CHILD(pid);
	}
	exit(0);
}

static void
charatatime(char *str)
{
	char *ptr;
	int	c;

	setbuf(stdout, NULL);
	for(ptr = str; (c=*ptr++); )
		putc(c, stdout);
}
