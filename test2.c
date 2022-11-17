#include <signal.h>
#include <stdio.h>

int main()
{
	int pid;
	int i = 0;

	printf("enter pid\n");
	scanf("%d", &pid);

	while (1)
	{
		kill(pid, SIGUSR1);
		printf("signals sent= %i\n", i++);
		usleep(100);
	}
	return (0);
}