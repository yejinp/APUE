#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

#define	QLEN	10
int a = 10;

int 
serv_listen(const char *name)
{
	int	fd, len, err, rval;
	struct	sockaddr_un	un;
	
	if((fd = socket(AF_UNIX, SOCK_STREAM,0)) < 0) {
		return (-1);
	}

	unlink(name);

	bzero(&un, sizeof(un));
	un.sun_family = AF_UNIX;
	strcpy(un.sun_path, name);
	len = offsetof(struct sockaddr_un, sun_path) + strlen(name);

	if(bind(fd, (struct sockaddr *)&un, len) < 0) {
		rval = -2;
		goto errout;
	}

	if(listen(fd, QLEN) < 0) {
		rval = -3;
		goto errout;
	}

	return (fd);
errout:
	err = errno;
	close(fd);
	errno = err;
	return (rval);
}
