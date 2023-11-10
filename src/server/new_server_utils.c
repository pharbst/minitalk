/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_server_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 23:56:19 by pharbst           #+#    #+#             */
/*   Updated: 2023/11/11 00:00:34 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new_minitalk.h"
#include "libftio.h"

void	add_uint_to_message(unsigned int what, t_client *client)
{
	client->message[client->byte++] = what >> 24;
	client->message[client->byte++] = what >> 16;
	client->message[client->byte++] = what >> 8;
	client->message[client->byte++] = what;
}

void	pause_client(t_client *client)
{
	client->timeout = utime();
	kill(client->pid, SIGUSR2);
}

unsigned long	utime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

t_client*	get_clients(void)
{
	static t_client	_clients[256];

	return (_clients);
}

int*	get_pids(void)
{
	static int	_pids[256];

	return (_pids);
}
