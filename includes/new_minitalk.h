/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_minitalk.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 03:21:05 by pharbst           #+#    #+#             */
/*   Updated: 2023/11/06 02:23:10 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEW_MINITALK_H
# define NEW_MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdbool.h>

// Client

typedef struct s_payload
{
	char*			message;
	unsigned int	message_len;
	bool			connection;
	bool			busy;
	int 			dest_pid;
}				t_payload;

t_payload*	get_payload(void);

void		sig_connect(int sig);
void		sig_controll(int sig);

// Server

typedef struct t_server
{
	char				*message;
	unsigned int		message_len;
	int					pid;
	int					bit;
	int					signal;
}

#endif