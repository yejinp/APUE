#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <string.h>
#include <strings.h>
#include <linux/if_ether.h>

#define BUFSIZE     1500

#define SOCKET_ERR_EXIT	1
#define SOCKETOPT_ERR_EXIT	2
#define SENDTO_ERR_EXIT	3

#define MAX_DATA_LEN 2048

char *patt = "%s\x85\x80\x00\x01\x00\x01%s\xc0\x0c\x00\x01\x00\x01\x00\x00\x0e\x10\x00\x04\x7f\x00\x00\x08";

size_t	g_send_fail_count = 0;

char answer_content[] = {0xc0, 0x0c, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 
						0x0e, 0x10, 0x00, 0x04, 0x7f, 0x00, 0x00, 0x08};

struct pseudohdr
{
	unsigned int	    saddr;
	unsigned int 	    daddr;
	char                zero;
	char                protocol;
	unsigned short      length;
};

#if 0
static inline unsigned add32_with_carry(unsigned a, unsigned b)
{
	asm("addl %2,%0\n\t"
	    "adcl $0,%0"
	    : "=r" (a)
	    : "0" (a), "rm" (b));
	return a;
}


/**
 * csum_fold - Fold and invert a 32bit checksum.
 * sum: 32bit unfolded sum
 *
 * Fold a 32bit running checksum to 16bit and invert it. This is usually
 * the last step before putting a checksum into a packet.
 * Make sure not to mix with 64bit checksums.
 */
static inline u_int16_t csum_fold(u_int32_t sum)
{
	__asm__(
		"  addl %1,%0\n"
		"  adcl $0xffff,%0"
		: "=r" (sum)
		: "r" (( u_int32_t)sum << 16),
		  "0" ((u_int32_t)sum & 0xffff0000)
	);
	return (u_int16_t)(~(u_int32_t)sum >> 16);
}

/**
 * csum_tcpup_nofold - Compute an IPv4 pseudo header checksum.
 * @saddr: source address
 * @daddr: destination address
 * @len: length of packet
 * @proto: ip protocol of packet
 * @sum: initial sum to be added in (32bit unfolded)
 *
 * Returns the pseudo header checksum the input data. Result is
 * 32bit unfolded.
 */
static inline u_int32_t
csum_tcpudp_nofold(u_int32_t saddr,/*big endian*/ u_int32_t daddr,/*big endian*/ u_int32_t len,
		  u_int8_t proto, u_int32_t sum)
{
	asm("  addl %1, %0\n"
	    "  adcl %2, %0\n"
	    "  adcl %3, %0\n"
	    "  adcl $0, %0\n"
		: "=r" (sum)
	    : "g" (daddr), "g" (saddr), "g" ((len + proto) << 8), "0" (sum));
	return sum;
}

/*
 * computes the checksum of the TCP/UDP pseudo-header
 * returns a 16-bit checksum, already complemented
 */
static inline u_int16_t csum_tcpudp_magic(u_int32_t saddr/*bigendian*/, u_int32_t daddr,/*bigendian*/
					u_int32_t len, u_int8_t proto,
					u_int32_t sum)
{
	return csum_fold(csum_tcpudp_nofold(saddr,daddr,len,proto,sum));
}

#endif

/* CRC16校验 */
unsigned short inline
checksum (unsigned short *buffer, unsigned short size)     
{  

	unsigned long cksum = 0;
	
	while(size > 1){
		cksum += *buffer++;
		size  -= sizeof(unsigned short);
	}
	
	if(size){
		cksum += *(unsigned char *)buffer;
	}
	
	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >> 16);		
	
	return((unsigned short )(~cksum));
}

unsigned short inline
checksum2(unsigned short *buffer1, unsigned short size1, unsigned short *buffer2, unsigned short size2)     
{  

	unsigned long cksum = 0;
	
	while(size1 > 1){
		cksum += *buffer1++;
		size1  -= sizeof(unsigned short);
	}
	
	if(size1){
		cksum += *(unsigned char *)buffer1;
	}
	
	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >> 16);		
	
	while(size2 > 1){
		cksum += *buffer2++;
		size2  -= sizeof(unsigned short);
	}
		
	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >> 16);
	
	if(size2){
		cksum += *(unsigned char *)buffer2;
	}
	return((unsigned short )(~cksum));
}

static inline int append_answer_info(char *buf, int query_len)
{
	char *p = buf;

	//skip ID
	p += 2;
	*p = 0x81;
	p++;
	*p = 0x80;
	p++;

	// 2 bytes questions
	p += 2;

	// set answers to 1
	p ++;
	*p = 1;
	p++;

	memcpy(buf + query_len, answer_content, sizeof(answer_content));
	return sizeof(answer_content) + query_len;
}

static inline int append_answer2raw(char *buf)
{
	char *p = buf;

	memcpy(buf, answer_content, sizeof(answer_content));
	return sizeof(answer_content);
}

int udp_reply_dns(int sockfd)
{
	char buffer[MAX_DATA_LEN], *p;
	struct sockaddr_in saddr, client;
	int sock, query_len, response_len , n;
	sock = socket(AF_INET, SOCK_DGRAM, 0);

	memset(&saddr, 0, sizeof(struct sockaddr_in));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(53);
	
	if(bind(sock, (struct sockaddr *)&saddr, sizeof(struct sockaddr_in)) < 0 ){
	  perror("bind failed");
	  exit(9);
	}

	while(1) {
		bzero(&buffer, MAX_DATA_LEN);
		n = recvfrom(sock, buffer, MAX_DATA_LEN, 0, (struct sockaddr*)&client, sizeof(client));
		if(n <= 0) {
			perror("recvfrom failed");
			continue;
		}
		p = buffer;
		response_len = append_answer_info(buffer, query_len);
		n = sendto(sock, buffer, response_len, 0, (struct sockaddr*)&client, sizeof(client));
		if(n < 0) {
			perror("sendto error");
		}
	}

	return 0;
}

//
void modify_ip_header(struct iphdr *pip)
{
	u_int32_t ip;

	//exchange ip address
	ip = pip->daddr;
	pip->daddr = pip->saddr;
	pip->saddr = ip;

	pip->id = 0;
	pip->check = 0;
	pip->ttl = 63;
}

void modify_udp_header(struct udphdr *pudp, int answer_len)
{
	u_int16_t port;
	// exchange port
	port = pudp->dest;
	pudp->dest = pudp->source;
	pudp->source = port;

	// reset checksum to 0
	pudp->check = 0x0;
	pudp->len = htons(htons(pudp->len) + answer_len);	
}

static int raw_handle_dns_pkt()
{
	int recvlen = 0, nsent, answer_len, iphlen;
	int rawfd = -1, fd;	
	int 	on = 1;
	struct sockaddr_in client, from;
	socklen_t calen = sizeof(client);
	char	  buf[BUFSIZE] = {0}, recvbuf[BUFSIZE] = {0}, *p;
	struct pseudohdr pseudoheader;	//UDP伪头部

	struct iphdr  *pip;
	struct udphdr *pudp;
	
	memset(&client, 0, sizeof(struct sockaddr_in));
	memset(&from, 0, sizeof(struct sockaddr_in));
	client.sin_family = AF_INET;
	client.sin_port = htons(53);
	if (inet_pton(AF_INET, "127.0.0.1", &client.sin_addr) <= 0)
		perror("inet_pton error ");

	fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_IP));	/* fd, used to recv pkts  */
	if(fd < 0) {
		perror("socket PF_PACKET failed");
		exit(SOCKET_ERR_EXIT);
	}

	rawfd = socket(AF_INET , SOCK_RAW, IPPROTO_UDP); //only used to send UDP packets
	if(rawfd < 0) {
		perror("socket raw icmp");
		exit(SOCKET_ERR_EXIT);
	}

/* don't set option IP_HDRINCL to tell the kernel send the packt depend on the socket creation */
	if(setsockopt(rawfd, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) < 0) {
		perror("setsockopt IP_HDRINCL error");
		exit(SOCKETOPT_ERR_EXIT);
	}

	while(1){
		recvlen = recvfrom(fd, recvbuf, BUFSIZE, 0, NULL, 0);//(struct sockaddr *)&from, sizeof(from));
		if(recvlen < 0) {
			perror("recvfrom error");
		}

		pip = (struct iphdr *)(recvbuf + 14);
		if(pip->protocol != 0x11) {
			continue;
		}

		iphlen = pip->ihl << 2;
		pudp =(struct udphdr *)(recvbuf + 14 + iphlen);
		if(pudp->dest != htons(53)) {
			continue;
		}

		// point to the payload of udp
		p = recvbuf + 14 + iphlen + 8;
		p += 2; //skip ID

		//modify the flags
		*p = 0x81;
		p ++;
		*p = 0x80;
		p++;

		//skip query count
		p += 2;

		// answer count = 1
		p++ ;
		*p = 0x01;
		
//		csum_tcpudp_magic(pip->saddr, pip->daddr, 0x11, );

		answer_len = append_answer2raw(recvbuf + recvlen);	
		modify_ip_header(pip);
		modify_udp_header(pudp, answer_len);
		
		pseudoheader.daddr = pip->daddr;
		pseudoheader.saddr = pip->saddr;
		pseudoheader.protocol = IPPROTO_UDP;
		pseudoheader.zero = 0;
		pseudoheader.length = htons(answer_len + recvlen - 14 - 20);
			
		pudp->check = checksum2((char *)&pseudoheader, sizeof(pseudoheader), recvbuf + 14 + 20, answer_len + recvlen - 14 - 20);

	again:	
		nsent = sendto(rawfd, recvbuf + 14, answer_len + recvlen - 14, 0, (struct sockaddr *)&client, calen);
		if(nsent < 0 ) { 
			if(errno == EINTR) {
				goto again;
			}
			else {
				perror("sento failed");
				g_send_fail_count ++;
			}
		} else {
			//printf("sent: %d recvlen: %d; answer_len:%d\n", nsent, recvlen, answer_len);
		}
		
	}
}

int
main(int argc, char *argv[])
{

	printf("start:\n");	
	raw_handle_dns_pkt();
}
