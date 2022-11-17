#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int x = 0;

void	signal_handler(int signum)
{
	printf("signal %d received\n", signum);
	x++;
}

int main()
{
	struct sigaction sa;
	sa.sa_handler = &signal_handler;
	sa.sa_flags = SA_RESTART;
	int i = 0;

	sigaction(SIGUSR1, &sa, NULL);
	while (1)
	{
		printf("|pid:%d | recieved signals = %i\n", getpid(), x);
		usleep(1);
	}
	return (0);
}