/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 03:32:14 by pharbst           #+#    #+#             */
/*   Updated: 2023/11/10 06:38:46 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new_minitalk.h"
#include "libftio.h"
#include <stdio.h>

int		sending(int bit_len, unsigned int what);
void	connect(void);
void	send_message(void);

int	main(int argc, char **argv)
{
	int			pid;
	size_t		len;
	t_payload	*payload;

	ft_printf("your pid: %d\n", getpid());
	if (argc != 3)
		return (ft_printf("Error: wrong number of arguments\n"), 0);
	pid = atoi(argv[1]);
	if (pid <= 0)
		return (ft_printf("Error: PID must be a positive number\n"), 0);
	payload = get_payload();
	len = ft_strlen(argv[2]);
	if (len > 0b11111111111111111111111111111111)
		return (ft_printf("Error: message is too long\n"), 0);
	payload->message = argv[2];
	payload->message_len = len;
	payload->dest_pid = pid;
	payload->connection = false;
	connect();
	send_message();
	return (0);
}

void	connect(void)
{
	t_payload		*payload;

	signal(SIGUSR1, &sig_connect);
	signal(SIGUSR2, &sig_connect);
	sending_loop(0, 1);
	payload = get_payload();
	if (!payload->answerd)
	{
		ft_putstr_fd("Error: Server is not responding\n", 1);
		exit(0);
	}
	signal(SIGUSR1, &sig_controll);
	signal(SIGUSR2, &sig_controll);
	if (sending(32, payload->message_len))
		exit(0);
}

void	debug_function1(unsigned int what)
{
	int	i;

	i = 0;
	while (i < 32)
	{
		if ((what >> (31 - i)) % 2)
			ft_putchar_fd('1', 1);
		else
			ft_putchar_fd('0', 1);
		if (i % 8 == 7)
		{
			ft_putstr_fd(" = ", 1);
			ft_putchar_fd(what >> (31 - i), 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
	ft_putchar_fd('\n', 1);
}

void	send_message(void)
{
	unsigned int	what;
	unsigned int	byte;
	int				i;
	t_payload		*payload;

	signal(SIGUSR1, &sig_controll);
	payload = get_payload();
	byte = 0;
	while (byte < payload->message_len)
	{
		i = 0;
		while (i < 4)
		{
			if (byte + i < payload->message_len)
				what = what << 8 | payload->message[byte + i];
			else
				what = what << 8;
			i++;
		}
		debug_function1(what);
		if (sending(32, what))
			exit(0);
		byte += 4;
	}
}

int	sending(int bit_len, unsigned int what)
{
	unsigned int	bit;
	unsigned int	i;
	unsigned int	j;
	t_payload		*payload;

	payload = get_payload();
	while ((--bit_len >= 0) && payload->answerd)
		sending_loop(what, bit_len);
	if (!payload->answerd)
			return (ft_putstr_fd("Error: lost connection to server\n", 1), 1);
	return (0);
}
