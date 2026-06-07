#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
	sigset_t set;

	sigfillset(&set);
	sigdelset(&set, SIGINT);
	sigdelset(&set, SIGQUIT);
	sigprocmask(SIG_SETMASK, &set, NULL);

	while(1);
	return 0;
}
