#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <syslog.h>
#include <signal.h>
#include <string.h>

sigset_t mask;
extern int already_running(void);
extern void daemonize(char *);

void
reread(void)
{
	/* ... */
}

void *
thr_fn(void *arg)
{
	int	err, signo;
	for( ; ; ) {
		err = sigwait(&mask, &signo);
		if(err) {
			syslog(LOG_ERR, "sigwait failed: %m");
			exit(1);
		}

		switch(signo) {
		case SIGHUP:
			syslog(LOG_INFO, "Re-reading configuration file");
			reread();
			break;

		case SIGTERM:
			syslog(LOG_INFO, "got SIGTERM; exting");
			exit(0);

		default:
			syslog(LOG_INFO, "unexpected signal %d\n", signo);
		}
	}

	return 0;
}

int
main(int argc, char **argv)
{
	int	err;
	pthread_t	tid;
	char	*cmd;
	struct sigaction	sa;

	if((cmd = strrchr(argv[0], '/')) == NULL) 
		cmd = argv[0];
	else
		cmd++;

	/*
	 *Become a daemon.
	 */

	daemonize(cmd);

	/*
	 * Make sure only one copy of the daemon is running.
	 */
	if(already_running()) {
		syslog(LOG_ERR, "daemon already running");
		exit(1);
	}

	/*
	 * Restore SIGHUP default and block all signals.
	 */

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if(sigaction(SIGHUP, &sa, NULL) < 0) {
		printf("%s: can't restore SIGHUP default\n", argv[0]);
		exit(9);
	}

	sigfillset(&mask);
	if((err = pthread_sigmask(SIG_BLOCK, &mask, NULL)) != 0) {
		printf("SIG_BLOCK error\n");
		exit(8);
	}

	/*
	 * Create a thread to handle SIGHUP and SIGTERM.
	 */
	err = pthread_create(&tid, NULL, thr_fn, 0);
	if(err) {
		printf("can't create thread\n");
		exit(err);
	}

	/*
	 * Proceed with the rest of the daemon.
	 */

	/* ... */
	exit(0);
}
