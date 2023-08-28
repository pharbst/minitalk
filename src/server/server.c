/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:45:06 by pharbst           #+#    #+#             */
/*   Updated: 2023/08/28 12:17:15 by pharbst          ###   ########.fr       */
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

int	get_index(t_handler *a, int pid)
{
	int	i;

	if (pid <= 0)
		return (-2);
	i = 0;
	while (i < MAX_PIDs)
	{
		if (a[i].pid == pid)
			return (i);
		else if(!a[i].pid)
			return (-1);
		i++;
	}
	return (-2);
}

int	save_massage(int sig, t_handler *a, int index)
{
	
}

void	new_handler(int sig, siginfo_t *siginfo, void *context)
{
	int					pid;
	int					index;
	t_handler	*a;

	a = siginfo->sa_value;

	pid = siginfo->si_pid;
	(void)context;
	index = get_index(siginfo.sa_value, pid);
	if (index < -1)
		return write(2, "Error: to many clients\n", 24);
	else if (index == -1 && sig == SIGUSR1)
	{
		add_pid(a, pid);
		ft_printf("Connection with %d established\n", pid);
	}
	if (save_massage(sig, a, index))
	{
		kill(pid, SIGUSR2);
		delete_entry(a, index);
		return ;
	}
	kill(pid, SIGUSR1);
	return ;
}

int	main(void)
{
	t_handler			a[MAX_PIDs];
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	sa.sa_value = a;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("Server PID: %d\n", getpid());
	while (1)
		pause();
}
