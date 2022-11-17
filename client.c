/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:45:38 by peter             #+#    #+#             */
/*   Updated: 2022/11/17 17:23:39 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
