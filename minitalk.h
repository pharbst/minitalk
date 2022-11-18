/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 00:22:53 by peter             #+#    #+#             */
/*   Updated: 2022/11/18 17:20:04 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include "libftio/includes/libftio.h"

typedef struct s_parity
{
	unsigned int	q0;
	unsigned int	q1;
	unsigned int	q2;
	unsigned int	q3;
	unsigned int	q4;
	unsigned int	q5;
	unsigned int	q6;
	unsigned int	q7;
	unsigned int	q8;
	unsigned int	k;
}	t_parity;

void	parity_check(bool *block, t_parity *parity);
void	set_parity_bits(bool *block);
bool	**encode_massage(char *str);

# endif