/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 00:18:24 by pharbst           #+#    #+#             */
/*   Updated: 2023/11/11 00:39:13 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new_minitalk.h"
#include "libftio.h"

static void	server_sig_handler(int sig, siginfo_t *info, void *ucontext);

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
		check_timeout();
	return (0);
}

static void	server_sig_handler(int sig, siginfo_t *info, void *ucontext)
{
	static t_busy	busy;
	int				*pids;
	t_client		*clients;

	clients = get_clients();
	pids = get_pids();
	if (busy.flag)
	{
		if (busy.pid != info->si_pid && get_index(info->si_pid, pids, false) >> 31)
			return (kill(info->si_pid, SIGUSR2));
		else if (busy.pid != info->si_pid)
			return (pause_client(&clients[get_index(info->si_pid, pids, false)]));
		return (controll_bits(sig, &clients[get_index(busy.pid, pids, false)], &busy));
	}
	if (get_index(info->si_pid, pids, false) >> 31)
	{
		if (sig != SIGUSR1)
			return ;
		if (get_index(info->si_pid, pids, true) >> 31)
			return (kill(info->si_pid, SIGUSR2));
		pids[get_index(info->si_pid, pids, true)] = info->si_pid;
		new_client(&clients[get_index(info->si_pid, pids, true)], info->si_pid);
		return ;
	}
	interpreter(&clients[get_index(info->si_pid, pids, false)], sig, false);
}
