/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 00:22:53 by peter             #+#    #+#             */
/*   Updated: 2022/11/23 19:45:12 by pharbst          ###   ########.fr       */
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
# include "libft/includes/libftio.h"

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
	int			j;
	int			pid;
	int			sig;
	int			i[4194304];
	bool		flag[4194304];
	char		*c[4194304][(INT_MAX / 1024) / 1024];
}	t_handler;

void	send_massage(int pid, char *massage);
void	connect(int pid);

#endif