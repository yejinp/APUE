#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>
#include <errno.h>

#define STALE 30

int
serv_accept(int listenfd, uid_t *uidptr)
{
	int	clifd, len, err, rval;
	time_t	staletime;
	struct sockaddr_un	un;
	struct stat	statbuf;

	len = sizeof(un);
	if((child = accept(listenfd, (struct sockaddr*)&un, &len)) < 0) {
		return (-1);
	}

	len -= offsetof(struct sockaddr_un, sun_path);
	un.sun_path[len] = 0;

	if(stat(un.sun_path, &statbuf) < 0) {
		rval = -2;
		goto errout;
	}

}
