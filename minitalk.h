/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peter <peter@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 00:22:53 by peter             #+#    #+#             */
/*   Updated: 2022/11/17 00:24:24 by peter            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>

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
}	t_parity;

void	parity_check(bool *block, t_parity *parity);

# endif