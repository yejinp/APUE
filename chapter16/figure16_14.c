#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>

#define		MAXADDRLEN	256
#define		BUFLEN		128

extern int connect_retry(int, const struct sockaddr *, socklen_t);

void
print_uptime(int sockfd)
{
	int	n;
	char	buf[BUFLEN];

	while(( n = recv(sockfd, buf, BUFLEN, 0)) > 0) {
		write(STDOUT_FILENO, buf, 0);
	}

	if(n < 0) {
		perror("recv error");
		exit(9);
	}
}

int
main(int argc, char *argv[])
{
	struct addrinfo *ailist, *aip;
	struct addrinfo hint;
	int 	sockfd, err;

	if(argc != 2) {
		printf("usage: %s <hostname>\n", argv[0]);
		exit(9);
	}

	bzero(&hint, sizeof(hint));

	hint.ai_socktype = SOCK_STREAM;

	if((err = getaddrinfo(argv[1], "ruptime", &hint, &ailist)) != 0) {
		printf("getaddrinfo error: %s\n", gai_strerror(err));
		exit(9);
	}

	for(aip = ailist; aip != NULL; aip = aip->ai_next) {
		if((sockfd = socket(aip->ai_family, SOCK_STREAM, 0)) < 0) {
			err = errno;
		}
		if(connect_retry(sockfd, aip->ai_addr, aip->ai_addrlen) < 0) {
			err = errno;
		} else {
			print_uptime(sockfd);
			exit(0);
		}
	}

	fprintf(stderr, "can't connect to %s: %s\n", argv[1], strerror(err));
	exit(1);
}
