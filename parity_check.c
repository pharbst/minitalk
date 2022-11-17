/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parity_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 00:22:30 by peter             #+#    #+#             */
/*   Updated: 2022/11/17 16:23:27 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	reset_parity(t_parity *parity)
{
	parity->q0 = 0;
	parity->q1 = 0;
	parity->q2 = 0;
	parity->q3 = 0;
	parity->q4 = 0;
	parity->q5 = 0;
	parity->q6 = 0;
	parity->q7 = 0;
	parity->q8 = 0;
	parity->k = 0;
}

void	parity_check(bool *block, t_parity *parity)
{
	reset_parity(parity);
	while (parity->k < 256)
	{
		if (block[parity->k] == 1)
			parity->q0++;
		if (parity->k % 2 == 1 && block[parity->k] == 1)
			parity->q1++;
		if (parity->k % 4 >= 2 && block[parity->k] == 1)
			parity->q2++;
		if (parity->k % 8 >= 4 && block[parity->k] == 1)
			parity->q3++;
		if (parity->k % 16 >= 8 && block[parity->k] == 1)
			parity->q4++;
		if (parity->k % 32 >= 16 && block[parity->k] == 1)
			parity->q5++;
		if (parity->k % 64 >= 32 && block[parity->k] == 1)
			parity->q6++;
		if (parity->k % 128 >= 64 && block[parity->k] == 1)
			parity->q7++;
		if (parity->k >= 128 && block[parity->k] == 1)
			parity->q8++;
		parity->k++;
	}	
}

static void	set_parity_bits_helper(bool *block, t_parity *parity)
{
	if (parity->q5 % 2 == 1)
		block[16] = 1;
	if (parity->q5 % 2 == 1)
		parity->q0++;
	if (parity->q6 % 2 == 1)
		block[32] = 1;
	if (parity->q6 % 2 == 1)
		parity->q0++;
	if (parity->q7 % 2 == 1)
		block[64] = 1;
	if (parity->q7 % 2 == 1)
		parity->q0++;
	if (parity->q8 % 2 == 1)
		block[128] = 1;
	if (parity->q8 % 2 == 1)
		parity->q0++;
	if (parity->q0 % 2 == 1)
		block[0] = 1;
}

void	set_parity_bits(bool *block, t_parity *parity)
{
	parity_check(block, &parity);
	if (parity->q1 % 2 == 1)
		block[1] = 1;
	if (parity->q1 % 2 == 1)
		parity->q0++;
	if (parity->q2 % 2 == 1)
		block[2] = 1;
	if (parity->q2 % 2 == 1)
		parity->q0++;
	if (parity->q3 % 2 == 1)
		block[4] = 1;
	if (parity->q3 % 2 == 1)
		parity->q0++;
	if (parity->q4 % 2 == 1)
		block[8] = 1;
	if (parity->q4 % 2 == 1)
		parity->q0++;
	set_parity_bits_helper(block, &parity);
}
