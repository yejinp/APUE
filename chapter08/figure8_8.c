#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int
main(void)
{
	pid_t pid;
	if((pid = fork()) < 0) {
		perror("fork error");
		exit(9);
	} else if(pid == 0) {
		if((pid = fork()) < 0) {
			perror("fork error");
			exit(9);
		} else if(pid > 0)
			exit(0); // parent from second fork == first child
	

		/* we're the second child; our parent becomes init as soon 
	 	* our real parent calls exit() in the statment above.
	 	* Here's where we'd continue executing, knowing that when
		* we're done, init will reap our status.
	 	*/
		sleep(2);
		printf("second child, parent pid = %d\n", getppid());
		exit(0);
	}

	if(waitpid(pid, NULL, 0) != pid) { // wait for first child
		perror("waitpid error");
		exit(8);
	}

	/* we're the parent(the original process); we continue executing,
	 * knowing that we're not the parent of the second child.
	 */
	exit(0);
}
