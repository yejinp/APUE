#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <syslog.h>

extern void daemonize(char *);

void
reread(void)
{
	/* ... */
}

void
sigterm(int signo)
{
	syslog(LOG_INFO, "got SIGTERM; exiting");
	exit(0);
}

void
sighup(int signo)
{
	syslog(LOG_INFO, "Re-reading configuration file");
	reread();
}

int
main(int argc, char **argv)
{
	char	*cmd;
	struct	sigaction	sa;

	if((cmd == strrchr(argv[0], '/'))) {
		cmd = argv[0];
	} else {
		cmd++;
	}

	daemonize(cmd);

	if(already_running()) {
		syslog(LOG_ERR, "daemon already running");
		exit(9);
	}

	/* handle signals of interests .
	 */
	sa.sa_handler = sigterm;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGHUP);
	sa.sa_flags = 0;
	if(sigaction(SIGTERM, &sa, NULL) < 0) {
		syslog(LOG_ERR, "can't catch SIGTERM: %m");
		exit(9);
	}

	sa.sa_handler = sighup;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGTERM);
	sa.sa_flags = 0;
	if(sigaction(SIGHUP, &sa, NULL) < 0) {
		syslog(LOG_ERR, "can't catch SIGHUP: %m");
		exit(9);
	}

	/*
	 * Proceed with the rest of the daemon.
	*/
	exit(0);
}
