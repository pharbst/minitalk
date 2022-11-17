/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_blocks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:51:39 by peter             #+#    #+#             */
/*   Updated: 2022/11/17 16:06:05 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minitalk.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>
#include "minitalk.h"

int	main(int argc, char **argv)
{
	char	*str;

	str = argv[1];
	if (argc != 2)
		return (0);
	
}


int main()
{
	char *str = "Hello World!1234567890PeterJule";
	unsigned char	i;
	bool			*massage = calloc(256, sizeof(bool));
	int j = 0;
	int k = 0;
	t_parity		parity;

	while (*str)
	{
		i = *str;
		while (k < 8)
		{
			if (j == 0 || j == 1 || j == 2 || j == 4 || j == 8 || j == 16 || j == 32 || j == 64 || j == 128)
				j++;
			if (i % 2 == 1)
			{
				massage[j] = 1;
				printf("1");
			}
			else
			{
				massage[j] = 0;
				printf("0");
			}
			i = i >> 1;
			j++;
			k++;
		}
		k = 0;
		printf(" ");
		str++;
	}
	printf("\n");
	k = 0;
	parity_check(massage, &parity);
	printf("q1 = %d\nq2 = %d\nq3 = %d\nq4 = %d\nq5 = %d\nq6 = %d\nq7 = %d\nq8 = %d\n", q1, q2, q3, q4, q5, q6, q7, q8);
	if (q1 % 2 == 1)
		massage[1] = 1;
	if (q1 % 2 == 1)
		q0++;
	if (q2 % 2 == 1)
	{
		q0++;
		massage[2] = 1;
	}
	if (q3 % 2 == 1)
	{
		q0++;
		massage[4] = 1;
	}
	if (q4 % 2 == 1)
	{
		q0++;
		massage[8] = 1;
	}
	if (q5 % 2 == 1)
	{
		q0++;
		massage[16] = 1;
	}
	if (q6 % 2 == 1)
	{
		q0++;
		massage[32] = 1;
	}
	if (q7 % 2 == 1)
	{
		q0++;
		massage[64] = 1;
	}
	if (q8 % 2 == 1)
	{
		q0++;
		massage[128] = 1;
	}
	printf("q0 = %d\n", q0);
	if (q0 % 2 == 1)
	{
		massage[0] = 1;
		q0++;
	}
	printf("q0 = %d\n", q0);
	k = 0;
	while (k < 256)
	{
		if (k == 0 || k == 1 || k == 2 || k == 4 || k == 8 || k == 16 || k == 32 || k == 64 || k == 128)
			printf("\033[0;31m");
		if (k % 16 == 0 && k != 0)
			printf("\n");
		printf("%d \033[0;37m", massage[k]);
		k++;
	}
	if (massage[165] == 1)
		massage[165] = 0;
	else
		massage[165] = 1;
	q0 = 0;
	q1 = 0;
	q2 = 0;
	q3 = 0;
	q4 = 0;
	q5 = 0;
	q6 = 0;
	q7 = 0;
	q8 = 0;
	k = 0;
	while (k < 256)
	{
		if (massage[k] == 1)
			q0++;
		if (k % 2 == 1 && massage[k] == 1)
			q1++;
		if (k % 4 >= 2 && massage[k] == 1)
			q2++;
		if (k % 8 >= 4 && massage[k] == 1)
			q3++;
		if (k % 16 >= 8 && massage[k] == 1)
			q4++;
		if (k % 32 >= 16 && massage[k] == 1)
			q5++;
		if (k % 64 >= 32 && massage[k] == 1)
			q6++;
		if (k % 128 >= 64 && massage[k] == 1)
			q7++;
		if (k >= 128 && massage[k] == 1)
			q8++;
		k++;
	}
	k = 0;
	if (q1 % 2 == 1)
		k = 1;
	k = k << 1;
	if (q2 % 2 == 1)
		k += 1;
	k = k << 1;
	if (q3 % 2 == 1)
		k += 1;
	k = k << 1;
	if (q4 % 2 == 1)
		k += 1;
	k = k << 1;
	if (q5 % 2 == 1)
		k += 1;
	k = k << 1;
	if (q6 % 2 == 1)
		k += 1;
	k = k << 1;
	if (q7 % 2 == 1)
		k += 1;
	k = k << 1;
	if (q8 % 2 == 1)
		k += 1;
	printf("\nq0 = %d\nq1 = %d\nq2 = %d\nq3 = %d\nq4 = %d\nq5 = %d\nq6 = %d\nq7 = %d\nq8 = %d\n", q0, q1, q2, q3, q4, q5, q6, q7, q8);
	printf("\nk = %d\n", k);
	k = 0;
	while (k < 256)
	{
		if (k == 0 || k == 1 || k == 2 || k == 4 || k == 8 || k == 16 || k == 32 || k == 64 || k == 128)
			printf("\033[0;31m");
		if (k % 16 == 0 && k != 0)
			printf("\n");
		printf("%d \033[0;37m", massage[k]);
		k++;
	}
	free(massage);
	return (0);
}