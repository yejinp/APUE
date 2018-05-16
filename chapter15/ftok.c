#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>

// this program demos the usage of ftok
int
main(int argc, char **argv)
{
	int id;
	key_t	key;
	if(argc != 3) {
		printf("usage: %s <filename> <id>\n", argv[0]);
		exit(9);
	}
	id = atoi(argv[2]);
	key = ftok(argv[1], id);
	printf("id = %d , key = %d\n", id, key);
	exit(0);
}
