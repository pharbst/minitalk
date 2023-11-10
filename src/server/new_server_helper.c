/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_server_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 07:56:05 by pharbst           #+#    #+#             */
/*   Updated: 2023/11/11 00:14:12 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new_minitalk.h"
#include "libftio.h"
#include <sys/time.h>

void	interpreter(t_client *client, int signal, bool controll)
{
	if (signal == SIGUSR1)
		client->what = client->what << 1 | 0;
	else if (signal == SIGUSR2)
		client->what = client->what << 1 | 1;
	client->bit++;
	if (!controll && client->bit == 32)
	{
		add_uint_to_message(client->what, client);
		client->bit = 0;
		client->what = 0;
	}
}

void	controll_bits(t_client *client, int signal, t_busy *busy)
{
	interpreter(client, signal, true);
	if (client->bit == 32)
	{
		client->message_len = client->what;
		client->message = ft_calloc(client->message_len + 1, sizeof(char));
		client->init = true;
		client->bit = 0;
		client->what = 0;
	}
}

int	get_index(int pid, int pids[256], bool	get_end)
{
	int	i;

	i = 0;
	while (i < 256)
	{
		if (pids[i] == pid)
			return (i);
		if (pids[i] == 0 && get_end)
			return (i);
		i++;
	}
	return (-1);
}

void	new_client(t_client *client, int pid)
{
	client->pid = pid;
	client->message_len = 0;
	client->init = false;
	client->what = 0;
	client->bit = 0;
	if (client->message)
		free(client->message);
	client->message = NULL;
	client->timeout = utime();
}

void	check_timeout()
{
	int				i;
	t_client		*clients;
	int				*pids;

	clients = get_clients();
	pids = get_pids();
	i = 0;
	while (i < 256)
	{
		if (clients[i].pid && utime() - clients[i].timeout > 10000000)
		{
			pids[i] = 0;
			ft_putstr_fd("Client with pid: ", 2);
			ft_putnbr_fd(clients[i].pid, 2);
			ft_putstr_fd(" timed out\n", 2);
			new_client(&clients[i], 0);
			clients[i].timeout = 0;
		}
	}
}
