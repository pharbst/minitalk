/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parity_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peter <peter@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 00:22:30 by peter             #+#    #+#             */
/*   Updated: 2022/11/17 00:22:42 by peter            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	parity_check(bool *block, t_parity *parity)
{
	unsigned int	k;
	
	k = 0;
	while (k < 256)
	{
		if (block[k] == 1)
			parity->q0++;
		if (k % 2 == 1 && block[k] == 1)
			parity->q1++;
		if (k % 4 >= 2 && block[k] == 1)
			parity->q2++;
		if (k % 8 >= 4 && block[k] == 1)
			parity->q3++;
		if (k % 16 >= 8 && block[k] == 1)
			parity->q4++;
		if (k % 32 >= 16 && block[k] == 1)
			parity->q5++;
		if (k % 64 >= 32 && block[k] == 1)
			parity->q6++;
		if (k % 128 >= 64 && block[k] == 1)
			parity->q7++;
		if (k >= 128 && block[k] == 1)
			parity->q8++;
		k++;
	}	
}
