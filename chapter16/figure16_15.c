#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <errno.h>
#include <syslog.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

#define	BUFLEN	128
#define QLEN	10

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif

extern int initserver(int, struct sockaddr *, socklen_t, int);

void
serve(int sockfd)
{
	int	clfd;
	FILE	*fp;
	char	buf[BUFLEN];

	for( ; ;) {
		clfd = accept(sockfd, NULL, NULL);
		if(clfd < 0) {
			syslog(LOG_ERR, "ruptimed: accept error: %s",
				strerror(errno));
			exit(1);
		}
		
		if((fp = popen("/usr/bin/uptime", "r")) == NULL) {
			sprintf(buf, "error: %s\n", strerror(errno));
			send(clfd, buf, strlen(buf), 0);
		} else {
			while(fgets(buf, BUFLEN, fp) != NULL) {
				send(clfd, buf, strlen(buf), 0);
			}
			pclose(fp);
		}
		close(clfd);
	}
}

int
main(int argc, char *argv[]) 
{
	struct	addrinfo	*ailist, *aip;
	struct  addrinfo	hint;
	int	sockfd, err, n;
	char	*host;

	if(argc != 1) {
		printf("usage: ruptimed\n");
		exit(9);
	}

#ifdef _SC_HOST_NAME_MAX
	n = sysconf(_SC_HOST_NAME_MAX);
	if(n < 0) // best buess
#endif
		n = HOST_NAME_MAX;

	host = malloc(n);
	if(host == NULL) {
		printf("mallocc error");
		exit(9);
	}
	if(gethostname(host, n) < 0) {
		printf("gethostname error\n");
		exit(9);
	}

	daemonize("ruptimed");
	bzero(&hint, sizeof(hint));
	hint.ai_flags = AI_CANONNAME;
	hint.ai_socktype = SOCK_STREAM;

	if((err = getaddrinfo(host, "ruptime", &hint, &ailist)) != 0) {
		syslog(LOG_ERR, "ruptimed: getaddrinfo error: %s", gai_strerror(err));
		exit(1);
	}

	for(aip = ailist; aip; aip = aip->ai_next) {
		if((sockfd = initserver(SOCK_STREAM, aip->ai_addr,
				aip->ai_addrlen, QLEN)) >= 0) {
			serve(sockfd);
			exit(0);
		}
	}

}
