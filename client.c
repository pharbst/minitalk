#include "minitalk.h"

bool	g_flag;
char	*g_massage;
int		g_i;

void	sig_connect(int sig)
{
	ft_printf("Connection established\n");
	g_flag = true;
}

bool	connect(int pid)
{
	int	i;
	int	j;

	signal(SIGUSR1, sig_connect);
	i = 0;
	while (i < 5 && g_flag == false)
	{
		kill(pid, SIGUSR1);
		j = 0;
		while (j < 32 && g_flag == false)
		{
			usleep(10);
			j++;
		}
		i++;
	}
	if (g_flag == false)
		return (false);
	return (true);
}

void	send_massage(int pid, char *str)
{
	signal(SIGUSR1, sig_massage);
}

int main(int argc, char **argv)
{
	bool	connected;

	if (argc != 3)
		return (ft_printf("Error: wrong number of arguments\npls enter PID of the server as first argument and message as second argument\n"), 0);
	connected = connect(atoi(argv[1]));
	g_massage = argv[2];
	if (connected == false)
		return (ft_printf("Error: Server not reachable or busy\n", atoi(argv[1])), 0);
	else
		send_message(atoi(argv[1]));
	return (0);
}