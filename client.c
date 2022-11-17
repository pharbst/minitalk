/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:45:38 by peter             #+#    #+#             */
/*   Updated: 2022/11/17 17:12:16 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static bool	**encode_massage(char *str)
{
	bool			**blocks;
	unsigned int	len;
	unsigned int	block_count;
	unsigned int	bit_count;
	unsigned int	i;
	t_parity		parity;

	len = ft_strlen(str) * 8;
	if (len % 247 == 0)
		block_count = len / 247;
	else
		block_count = len / 247 + 1;
	blocks = (bool **)ft_calloc(block_count + 1, sizeof(bool *));
	while (block_count--)
		blocks[block_count] = (bool *)ft_calloc(256, sizeof(bool));
	//blockcount is -1 here
	i = 0;
	while (blocks[++block_count])
	{
		bit_count = 0;
		while (bit_count < 256)
		{
			if (i == 8)
				str++;
			if (i == 8)
				i = 0;
			if (bit_count == 0 || bit_count == 1 || bit_count == 2 || bit_count == 4 || bit_count == 8 || bit_count == 16 || bit_count == 32 || bit_count == 64 || bit_count == 128)
				bit_count++;
			if (*str % 2 == 1)
				blocks[block_count][bit_count] = 1;
			else
				blocks[block_count][bit_count] = 0;
			// printf("%d", blocks[block_count][bit_count]);
			*str = *str >> 1;
			bit_count++;
			i++;
		}
	}
	while (--block_count)
		set_parity_bits(blocks[block_count], &parity);
	return (blocks);
}

int	main(int argc, char **argv)
{
	bool			**blocks;
	unsigned int	i;
	
	if (argc != 2)
		write(1, "Error: Wrong number of arguments", 32);
	blocks = encode_massage(argv[1]);
	i = 0;
	while (blocks[i])
	{
		printf("%p\n", blocks[i]);
		i++;
	}
		printf("%p\n", blocks[i]);
	return (0);
}
