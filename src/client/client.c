/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 03:32:14 by pharbst           #+#    #+#             */
/*   Updated: 2023/11/16 10:59:19 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	sending(int bit_len, unsigned int what);
static void	connect(void);
static void	send_message(void);

int	main(int argc, char **argv)
{
	int			pid;
	size_t		len;
	t_payload	*payload;

	ft_printf("Client: your pid: %d\n", getpid());
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

static void	connect(void)
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

static void	send_message(void)
{
	unsigned int	what;
	unsigned int	byte;
	int				i;
	t_payload		*payload;

	signal(SIGUSR1, &sig_controll);
	signal(SIGUSR2, &sig_controll);
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
		if (sending(32, what))
			exit(0);
		byte += 4;
	}
}

static int	sending(int bit_len, unsigned int what)
{
	t_payload		*payload;

	payload = get_payload();
	while ((--bit_len >= 0) && payload->answerd)
		sending_loop(what, bit_len);
	if (!payload->answerd)
		return (ft_putstr_fd("Error: lost connection to server\n", 1), 1);
	return (0);
}
