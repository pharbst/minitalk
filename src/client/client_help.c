/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 19:26:01 by pharbst           #+#    #+#             */
/*   Updated: 2023/11/02 05:02:15 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

bool	g_connected;
bool	g_flag;

void	sig_connect(int sig)
{
	if (sig)
	{
		ft_printf("Connection confirmed\n");
		g_connected = true;
	}
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
	if (sig)
		g_flag = true;
}

void	massage_helper(t_send *send)
{
	if ((send->c >> send->bit) % 2 == 1)
		kill(send->pid, SIGUSR1);
	else
		kill(send->pid, SIGUSR2);
	send->response = 0;
	while (g_flag == false && send->response++ < 500)
		usleep(1);
	if (g_flag == true)
	{
		send->bit--;
		send->trys = 0;
		g_flag = false;
	}
	else
		send->trys++;
	if (send->bit < 0)
	{
		send->index++;
		send->bit = 7;
		send->c = send->massage[send->index];
	}
}

void	send_massage(int pid, char *massage)
{
	t_send	send;

	signal(SIGUSR1, &sig_send);
	send.trys = 0;
	send.pid = pid;
	send.bit = 7;
	send.index = 0;
	send.len = ft_strlen(massage);
	send.massage = massage;
	send.c = massage[send.index];
	while (send.trys < 10 && send.index <= send.len)
		massage_helper(&send);
	if (send.trys == 10)
		ft_printf("Server not responding\n");
	else
		ft_printf("Message got printed\n");
}

start = 8bit {establish connection = 1bit, massage length bit length = 7bit (max 64bits)}
4294967296 = 32bit
unicode:
18446744073709551616 = 64bit