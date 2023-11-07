/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_minitalk.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 03:21:05 by pharbst           #+#    #+#             */
/*   Updated: 2023/11/07 05:19:05 by pharbst          ###   ########.fr       */
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
	int 			dest_pid;
	bool			connection;
	bool			busy;
	bool			answerd;
} t_payload;

t_payload*	get_payload(void);

void		sig_connect(int sig);
void		sig_controll(int sig);

// Server

typedef struct s_client
{
	int					pid;
	char				*message;
	unsigned int		message_len;
	int					bit;
	int					signal;
	unsigned long		last_signal;
} t_client;

#endif