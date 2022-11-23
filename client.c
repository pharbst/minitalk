/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:56:34 by pharbst           #+#    #+#             */
/*   Updated: 2022/11/23 19:53:38 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(int argc, char **argv)
{
	int	pid;

	ft_printf("your pid: %d\n", getpid());
	if (argc != 3)
		return (ft_printf("Error: wrong number of arguments\n"), 0);
	pid = atoi(argv[1]);
	if (pid <= 0)
		return (ft_printf("Error: PID must be a positive number\n"), 0);
	connect(pid);
	send_massage(pid, argv[2]);
	return (0);
}
