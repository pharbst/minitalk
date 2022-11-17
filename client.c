/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:45:38 by peter             #+#    #+#             */
/*   Updated: 2022/11/17 18:38:03 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(int argc, char **argv)
{
	bool			**blocks;
	unsigned int	i;
	unsigned int	k;
	
	if (argc != 2)
		write(1, "Error: Wrong number of arguments", 32);
	blocks = encode_massage(argv[1]);
	i = 0;
	while (blocks[i])
	{
		printf("%p\n", blocks[i]);
		k = 0;
		while (k < 256)
		{
			if (k == 0 || k == 1 || k == 2 || k == 4 || k == 8 || k == 16 || k == 32 || k == 64 || k == 128)
				printf("\033[0;31m");
			if (k % 16 == 0 && k != 0)
				printf("\n");
			printf("%d \033[0;37m", blocks[i][k]);
			k++;
		}
		printf("\n\n\n");
		i++;
	}
	printf("%p\n", blocks[i]);
	return (0);
}
