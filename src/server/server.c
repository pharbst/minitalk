/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 23:46:08 by pharbst           #+#    #+#             */
/*   Updated: 2023/11/16 10:53:11 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	server_sig_handler(int sig, siginfo_t *info, void *ucontext);
static void	sig_int(int sig, siginfo_t *info, void *ucontext);

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
	sigaction(SIGINT, &sa_int, NULL);
	ft_printf("Server PID: %d\n", getpid());
	while (1)
		usleep(100000);
	return (0);
}

void	server_sig_handler(int signal, siginfo_t *info, void *context)
{
	int			*pids;
	t_client	*clients;
	int			index;
	int			empty_pos;

	(void)context;
	clients = get_clients();
	pids = get_pids();
	index = get_index(info->si_pid, pids, false);
	empty_pos = get_index(0, pids, true);
	if (index >> 31 && signal == SIGUSR1)
		new_client(info->si_pid, clients, pids, empty_pos);
	else
	{
		interpreter(&clients[index], signal);
		clients[index].timeout = utime();
		kill(info->si_pid, SIGUSR1);
	}
}

void	sig_int(int sig, siginfo_t *info, void *ucontext)
{
	int			i;
	t_client	*clients;
	int			*pids;

	(void)info;
	(void)ucontext;
	(void)sig;
	clients = get_clients();
	pids = get_pids();
	ft_putstr_fd("\nShutting down Server...\n", 1);
	ft_putstr_fd("clean up clients...\n", 1);
	i = -1;
	while (++i < 256)
		delete_client(i, clients, pids);
	ft_putstr_fd("Done\n", 1);
	exit(0);
}
