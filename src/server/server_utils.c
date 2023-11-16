/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 00:32:07 by pharbst           #+#    #+#             */
/*   Updated: 2023/11/16 10:53:21 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	delete_client(int index, t_client *clients, int *pids)
{
	if (!clients[index].pid)
		return ;
	if (clients[index].message)
		free(clients[index].message);
	ft_bzero(&clients[index], sizeof(t_client));
	pids[index] = 0;
}

void	new_client(int pid, t_client *clients, int *pids, int index)
{
	if (index >> 31)
	{
		kill(pid, SIGUSR2);
		return ;
	}
	pids[index] = pid;
	clients[index].pid = pid;
	clients[index].timeout = utime();
	kill(pid, SIGUSR1);
}

int	get_index(int pid_looking_for, int *pid_list, bool empty)
{
	int	i;

	i = -1;
	while (++i < 256)
	{
		if (empty && !pid_list[i])
			return (i);
		if (!empty && pid_list[i] == pid_looking_for)
			return (i);
	}
	return (-1);
}

t_client	*get_clients(void)
{
	static t_client	clients[256];

	return (clients);
}

int	*get_pids(void)
{
	static int	pids[256];

	return (pids);
}
