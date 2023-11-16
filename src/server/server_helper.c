/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 00:45:01 by pharbst           #+#    #+#             */
/*   Updated: 2023/11/16 10:57:18 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	interpreter(t_client *client, int signal)
{
	if (signal == SIGUSR1)
		client->what = client->what << 1 | 0;
	else if (signal == SIGUSR2)
		client->what = client->what << 1 | 1;
	client->bit++;
	if (client->bit == 32)
	{
		if (client->init)
			add_uint_to_message(client->what, client);
		else
		{
			client->message_len = client->what;
			client->init = true;
			client->message = ft_calloc(client->message_len + 4, sizeof(char));
		}
		client->bit = 0;
	}
	if (client->init && client->byte >= client->message_len)
	{
		ft_putstr_fd(client->message, 1);
		write(1, "\n", 1);
		delete_client(get_index(client->pid, get_pids(), false),
			get_clients(), get_pids());
	}
}

void	add_uint_to_message(unsigned int what, t_client *client)
{
	client->message[client->byte++] = what >> 24;
	client->message[client->byte++] = what >> 16;
	client->message[client->byte++] = what >> 8;
	client->message[client->byte++] = what;
}

unsigned long	utime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}
