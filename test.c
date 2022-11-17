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
	unsigned int x = 245;
	unsigned int y = 0;
	if (x % 245 == 0)
		y = x / 245;
	else
		y = x / 245 + 1;

	printf("x = %d, y = %d\n", x, y);
	return 0;
}