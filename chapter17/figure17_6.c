#include <unistd.h>

/*
 * return a STREAMS-based pipe, with the two file descrpitors
 * returned in fd[0] and fd[1].
*/
int
s_pipe(int fd[2])
{
	return 	(pipe(fd));
}
