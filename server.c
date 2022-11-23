/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:45:06 by pharbst           #+#    #+#             */
/*   Updated: 2022/11/22 15:30:40 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	print_block(char *block)
{
	int	i;

	i = 0;
	while (block[i] && i < 1024)
		write(1, &block[i++], 1);
}

void	sig_handler(int sig, siginfo_t *siginfo, void *context)
{
	int			j;
	int			pid;
	static int	i[4194304];
	static bool	flag[4194304];
	static char	*c[4194304][(INT_MAX / 1024) / 1024];

	pid = siginfo->si_pid;
	(void)context;
	if (flag[pid] == 0 && sig == SIGUSR1)
	{
		ft_printf("Connection established with %d\n", pid);
		flag[pid] = 1;
		kill(pid, SIGUSR1);
		usleep(100);
	}

	if (flag[pid] == 1)
	{
		if (i[pid] > INT_MAX / 1024)
			ft_printf("Error massage of %d is to long\n", pid);
		if (i[pid] < 0)
			kill(pid, SIGUSR2);
		if (!c[pid][(i[pid] / 8) / 1024])
			c[pid][(i[pid] / 8) / 1024] = ft_calloc(1024, sizeof(char));
		if (sig == SIGUSR1)
			c[pid][(i[pid] / 8) / 1024][(i[pid] / 8) % 1024] = (c[pid][(i[pid] / 8) / 1024][(i[pid] / 8) % 1024] << 1) + 1;
		if (sig == SIGUSR2)
			c[pid][(i[pid] / 8) / 1024][(i[pid] / 8) % 1024] = (c[pid][(i[pid] / 8) / 1024][(i[pid] / 8) % 1024] << 1);
		j = 0;
		if (i[pid] / 8 != 0 && i[pid] % 8 == 0 && c[pid][(i[pid] / 8) / 1024][(i[pid] / 8) % 1024] == '\0')
		{
			while (c[pid][j])
				print_block(c[pid][j++]);
			write(1, "\n", 1);
			j = 0;
			while (c[pid][j])
				free(c[pid][j++]);
			i[pid] = 0;
		}
		i[pid]++;
	}
	kill(pid, SIGUSR1);
}

int	main()
{
	struct sigaction	sa;
	{
		sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = sig_handler;
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
	};
	printf("Server is running\n");
	fflush(stdout);
	ft_printf("Server PID: %d\n", getpid());
	while (1)
		pause();
}
