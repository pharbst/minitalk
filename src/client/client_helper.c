/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_client_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 00:08:44 by pharbst           #+#    #+#             */
/*   Updated: 2023/11/16 10:59:24 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sending_loop(unsigned int what, int bit)
{
	unsigned int	i;
	unsigned int	j;
	t_payload		*payload;

	payload = get_payload();
	i = 0;
	payload->answerd = false;
	while (i++ < 16 && !payload->answerd)
	{
		payload->busy = true;
		while (payload->busy)
		{
			payload->busy = false;
			payload->answerd = false;
			if ((what >> bit) % 2)
				kill(payload->dest_pid, SIGUSR2);
			else
				kill(payload->dest_pid, SIGUSR1);
			j = 0;
			while (!payload->answerd && j++ < 128000)
				usleep(1);
			if (payload->busy)
				usleep(128000);
		}
	}
}

t_payload	*get_payload(void)
{
	static t_payload	_payload;

	return (&_payload);
}

void	sig_controll(int sig)
{
	t_payload	*payload;

	payload = get_payload();
	if (sig == SIGUSR1)
	{
		payload->answerd = true;
		payload->busy = false;
	}
	else if (sig == SIGUSR2)
	{
		payload->answerd = true;
		payload->busy = true;
	}
}

void	sig_connect(int sig)
{
	t_payload	*payload;

	payload = get_payload();
	if (sig == SIGUSR1)
	{
		ft_printf("Client: Connection confirmed\n");
		payload->connection = true;
		payload->busy = false;
		payload->answerd = true;
	}
	else if (sig == SIGUSR2)
	{
		ft_putstr_fd("Server is busy try to connect again in 128ms\n", 1);
		payload->busy = true;
		payload->answerd = true;
	}
}
