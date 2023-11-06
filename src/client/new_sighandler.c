/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_sighandler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 00:08:44 by pharbst           #+#    #+#             */
/*   Updated: 2023/11/06 02:37:39 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new_minitalk.h"

void	sig_controll(int sig)
{
	t_payload	*payload;

	payload = get_payload();
	if (sig == SIGUSR1)
		payload->busy = false;
}

void	sig_connect(int sig)
{
	t_payload	*payload;

	payload = get_payload();
	if (sig == SIGUSR1)
	{
		ft_printf("Connection confirmed\n");
		payload->connection = true;
		payload->busy = false;
	}
	else if (sig == SIGUSR2)
	{
		ft_putstr_fd("Server is busy try to connect again in 128ms\n", 1);
		payload->busy = true;
	}
}
