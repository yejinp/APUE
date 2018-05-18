#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

#define		MAXSLEEP	10
int
connect_retry(int sockfd, const struct sockaddr *addr, socklen_t alen)
{
	int 	nsec;

	for(nsec = 1; nsec <= MAXSLEEP; nsec <<= 1) {
		if(connect(sockfd, addr, alen) == 0) {
			/*
			 * Connection acceptd.
			 */
			return (0);
		}

		/*
		 * Delay before trying again.
		 */

		if(nsec <= MAXSLEEP / 2) {
			sleep(nsec);
		}
	}

	return -1;
}
