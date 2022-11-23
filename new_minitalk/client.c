/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:56:34 by pharbst           #+#    #+#             */
/*   Updated: 2022/11/23 17:25:48 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

bool	g_connected;
bool	g_flag;

void	sig_connect(int sig)
{
	ft_printf("Connection established\n");
	g_connected = true;
}

void	connect(int pid)
{
	int	i;
	int	j;

	signal(SIGUSR1, sig_connect);
	i = 0;
	while (i < 5 && g_connected == false)
	{
		ft_printf("Connection signal sent\n");
		kill(pid, SIGUSR1);
		j = 0;
		while (j < 32 && g_connected == false)
		{
			usleep(10);
			j++;
		}
		i++;
	}
	if (g_connected == false)
	{
		ft_printf("Connection failed\n");
		exit(0);
	}
}

void	sig_send(int sig)
{
	g_flag = true;
	// ft_printf("Signal received\n");
}

void	send_massage(int pid, char *massage)
{
	int		trys;
	int		len;
	int		response;
	int		index;
	int		bit;
	char	c;

	signal(SIGUSR1, sig_send);
	trys = 0;
	bit = 7;
	index = 0;
	len = ft_strlen(massage);
	// write(1, "Debug here\n", 11);
	c = massage[index];
	while (trys < 10 && index <= len)
	{
		if ((c >> bit) % 2 == 1)
		{
			// ft_printf("1 sent\n");
			kill(pid, SIGUSR1);
		}
		else
		{
			// ft_printf("0 sent\n");
			kill(pid, SIGUSR2);
		}
		response = 0;
		while (g_flag == false && response++ < 500)
			usleep(1);
		if (g_flag == true)
		{
			bit--;
			trys = 0;
			g_flag = false;
		}
		else
			trys++;
		if (bit < 0)
		{
			index++;
			bit = 7;
			c = massage[index];
		}
	}
	if (trys == 10)
		ft_printf("Server not responding\n");
	else
		ft_printf("Message got printed\n");
}

int	main(int argc, char **argv)
{
	int	pid;
	
	ft_printf("pid: %d\n", getpid());
	if (argc != 3)
		return (ft_printf("Error: wrong number of arguments\npls enter PID of the server as first argument and message as second argument\n"), 0);
	pid = atoi(argv[1]);
	if (pid <= 0)
		return (ft_printf("Error: PID must be a positive number\n"), 0);
	connect(pid);
	send_massage(pid, argv[2]);
	return (0);
}