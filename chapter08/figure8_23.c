#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>

int
main(void)
{
	int	status;
	if((status = system("date")) < 0) {
		perror("system() error");
	}
	pr_exit(status);
	
	if((status = system("nosuchcommand")) < 0) {
		perror("system error");
	}
	pr_exit(status);

	
	if((status = system("who; exit 44")) < 0) {
		perror("system error");
	}
	pr_exit(status);

	exit(0);
}
