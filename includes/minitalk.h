/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 00:22:53 by peter             #+#    #+#             */
/*   Updated: 2023/08/28 11:43:03 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <limits.h>
# include "libftio.h"

# ifndef MAX_PIDs
#  define MAX_PIDs 1024
# endif

typedef struct s_send
{
	char	c;
	int		trys;
	int		pid;
	int		len;
	int		response;
	int		index;
	int		bit;
	char	*massage;
}				t_send;

typedef struct s_handler
{
	// int			j;
	// int			pid;
	// int			sig;
	// int			i[MAX_PID];
	// bool		flag[MAX_PID];
	// char		*c[MAX_PID][(INT_MAX / 1024) / 1024];

	int		pid;
	char	**massage;
}	t_handler;

void	send_massage(int pid, char *massage);
void	connect(int pid);

#endif