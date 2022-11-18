/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoding.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:16:26 by pharbst           #+#    #+#             */
/*   Updated: 2022/11/18 17:26:47 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	encode_helper(bool **blocks, unsigned int block_count, unsigned int *i, char *str, unsigned int len)
{
	unsigned int	bit_count;
	unsigned char	c;

	bit_count = 3;
	while (bit_count < 256 && *i <= len)
	{
		if (*i % 8 == 0)
			c = str[*i / 8];
		if (bit_count == 0 || bit_count == 1 || bit_count == 2 || bit_count == 4 || bit_count == 8 || bit_count == 16 || bit_count == 32 || bit_count == 64 || bit_count == 128)
			bit_count++;
		if (c / 128 == 1)
			blocks[block_count][bit_count] = 1;
		else
			blocks[block_count][bit_count] = 0;
		c = c << 1;
		bit_count++;
		*i = *i + 1;
	}
}

bool	**encode_massage(char *str)
{
	bool			**blocks;
	unsigned int	len;
	int				block_count;
	unsigned int	bit_count;
	unsigned int	i;

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
		encode_helper(blocks, block_count, &i, str, len);
	printf("blockcount: %i\n", block_count);
	while (--block_count >= 0)
		set_parity_bits(blocks[block_count]);
	return (blocks);
}
