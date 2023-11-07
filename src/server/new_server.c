/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 00:18:24 by pharbst           #+#    #+#             */
/*   Updated: 2023/11/07 05:04:13 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new_minitalk.h"
#include "libftio.h"

void	server_sig_handler(int sig, siginfo_t *info, void *ucontext)
{
	int			pid;
	t_client	client;
	static int	busy;

	pid = info->si_pid;
	if (exist(pid) && busy)
		kill(pid, SIGUSR2);
	else if (exist(pid) && !busy)
	{
		add(pid);
		busy = pid;
		kill(pid, SIGUSR1);
	}
	else if (busy == pid )
	{
		// reieving controll bits
	}
	else if (busy && busy != pid)
		kill(pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = server_sig_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("Server PID: %d\n", getpid());
	while (1)
		pause();
}
