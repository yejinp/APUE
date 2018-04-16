#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <stddef.h>

int main(int argc, char *argv[])
{
	int 	fd, size;
	struct	sockaddr_un	un;
	
	un.sun_family = AF_UNIX;
	strcpy(un.sun_path, "foo.socket");
	if((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
		printf("socket failed.\n");
		exit(9);
	}

	size = offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path);
	//if(bind(fd, (struct sockaddr *)&un, size) < 0) {
	if(bind(fd, (struct sockaddr *)&un, sizeof(un)) < 0) {
		printf("bind failed.\n");
		exit(8);
	}

	printf("UNIX domain socket bound\n");
	exit(0);
}
