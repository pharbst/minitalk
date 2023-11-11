/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 00:18:24 by pharbst           #+#    #+#             */
/*   Updated: 2023/11/11 00:47:09 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new_minitalk.h"
#include "libftio.h"

static void	server_sig_handler(int sig, siginfo_t *info, void *ucontext);
static void	sig_int(void);

int	main(void)
{
	struct sigaction	sa;
	struct sigaction	sa_int;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &server_sig_handler;
	ft_bzero(&sa_int, sizeof(sa_int));
	sa_int.sa_sigaction = &sig_int;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGINT, , NULL);
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

static void	sig_int(void)
{
	t_client	*clients;
	int			i;

	clients = get_clients();
	ft_printf("Shutting down Server\n");
	i = 0;
	ft_printf("cleaning up clients\n");
	while (i < 256)
	{
		if (clients[i].message)
			free(clients[i].message);
		i++;
	}
	ft_printf("Server is down\n");
	exit(0);
}
