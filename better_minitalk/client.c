/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 01:53:39 by pharbst           #+#    #+#             */
/*   Updated: 2022/11/22 02:30:46 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sig_handler(int sig, siginfo_t *siginfo, void *context)
{
	static int	i;
	static int	pid;


	(void)context;
	if (i == 0)
		pid = siginfo->si_pid;
	if (sig == SIGUSR1)
	{
		if (i == 0)
			ft_printf("Connection established with %d\n", pid);
		i++;
	}
	if (sig == SIGUSR2)
	{
		ft_printf("Error: Server %d is not running\n", pid);
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3)
		return (ft_printf("Error no PID or message\npls enter PID of the server as first argument and message as second argument\n"), 0);
	struct sigaction	sa;
	struct sigaction	sa;
	{
		sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = sig_handler;
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
	};
	kill(ft_atoi(argv[1]), SIGUSR1);
	while(1)
	{
		usleep(1);
		
	}
}
