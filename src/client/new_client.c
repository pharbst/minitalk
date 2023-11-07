/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 03:32:14 by pharbst           #+#    #+#             */
/*   Updated: 2023/11/07 05:24:33 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new_minitalk.h"
#include "libftio.h"

t_payload*	get_payload(void);
void		connect(void);
void		send_controll_bits(void);

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
	unsigned int	i;
	t_payload		*payload;

	signal(SIGUSR1, &sig_connect);
	signal(SIGUSR2, &sig_connect);
	payload = get_payload();
	payload->busy = true;
	while (payload->busy)
	{
		kill(payload->dest_pid, SIGUSR1);
		payload->busy = false;
		i = 0;
		while (i++ < 1280 && !payload->busy && !payload->connection)
			usleep(1);
	}
	if (payload->connection)
		ft_printf("Connection established\n");
	else
	{
		ft_putstr_fd("Error: Connection Failed\n", 1);
		exit(0);
	}
	if (sending(32, payload->message_len))
		exit(0);
}

void	send_message(void)
{
	unsigned int	what;
	unsigned int	byte;
	unsigned int	i;
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
				what |= payload->message[byte + i] << (8 * i);
			else
				what = what << 8;
			i++;
		}
		if (sending(32, what))
			exit(0);
		byte += 4;
	}
}

int	sending(unsigned int bit_len, unsigned int what)
{
	unsigned int	bit;
	unsigned int	i;
	unsigned int	j;
	t_payload		*payload;

	payload = get_payload();
	bit = bit_len - 1;
	while (bit >= 0 && payload->answerd)
	{
		payload->answerd = false;
		j = 0;
		while (j++ < 16 && !payload->answerd)
		{
			if ((what >> bit) % 2)
				kill(payload->dest_pid, SIGUSR2);
			else
				kill(payload->dest_pid, SIGUSR1);
			i = 0;
			while (!payload->answerd && i++ < 1280)
				usleep(1);
			if (payload->busy)
			{
				usleep(128000);
				payload->busy = false;
				payload->answerd = false;
			}
		}
		bit--;
	}
	if (!payload->answerd)
			return (ft_putstr_fd("Error: Server is not responding\n", 1), 1);
	return (0);
}

t_payload*	get_payload(void)
{
	static t_payload	_payload;

	return (&_payload);
}
