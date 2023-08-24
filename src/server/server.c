/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:45:06 by pharbst           #+#    #+#             */
/*   Updated: 2022/11/23 19:53:20 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	print_massage(char **block)
{
	int	i;
	int	j;

	i = 0;
	while (block[i])
	{
		j = 0;
		while (block[i][j] && j < 1024)
		{
			ft_printf("%c", block[i][j]);
			j++;
		}
		i++;
	}
}

void	handler_helper(t_handler *a)
{
	if (a->i[a->pid] < 0)
		kill(a->pid, SIGUSR2);
	if (!a->c[a->pid][(a->i[a->pid] / 8) / 1024])
		a->c[a->pid][(a->i[a->pid] / 8) / 1024] = ft_calloc(1025, sizeof(char));
	if (a->sig == SIGUSR1)
		a->c[a->pid][(a->i[a->pid] / 8) / 1024][(a->i[a->pid] / 8) % 1024]
			= (a->c[a->pid][(a->i[a->pid] / 8)
				/ 1024][(a->i[a->pid] / 8) % 1024] << 1) + 1;
	if (a->sig == SIGUSR2)
		a->c[a->pid][(a->i[a->pid] / 8) / 1024][(a->i[a->pid] / 8) % 1024]
			= (a->c[a->pid][(a->i[a->pid]
					/ 8) / 1024][(a->i[a->pid] / 8) % 1024] << 1);
	a->j = 0;
	if (a->i[a->pid] / 8 != 0 && a->i[a->pid] % 8 == 7
		&& a->c[a->pid][(a->i[a->pid] / 8)
		/ 1024][(a->i[a->pid] / 8) % 1024] == '\0')
	{
		print_massage(a->c[a->pid]);
		write(1, "\n", 1);
		a->j = 0;
		while (a->c[a->pid][a->j])
			free(a->c[a->pid][a->j++]);
		a->i[a->pid] = 0;
	}
	a->i[a->pid]++;
}

void	sig_handler(int sig, siginfo_t *siginfo, void *context)
{
	static t_handler	a;

	a.sig = sig;
	a.pid = siginfo->si_pid;
	(void)context;
	if (a.pid < 1)
		return ;
	if (a.flag[a.pid] == 0 && sig == SIGUSR1)
	{
		ft_printf("Connection established with %d\n", a.pid);
		a.flag[a.pid] = 1;
		kill(a.pid, SIGUSR1);
	}
	else if (a.flag[a.pid] == 1)
	{
		if (a.i[a.pid] > INT_MAX / 1024)
			ft_printf("Error: massage of %d is to long\n", a.pid);
		handler_helper(&a);
	}
	kill(a.pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("Server PID: %d\n", getpid());
	while (1)
		pause();
}
