/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 00:37:53 by pharbst           #+#    #+#             */
/*   Updated: 2023/11/16 11:01:41 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include "libftio.h"

// Client

typedef struct s_payload
{
	char			*message;
	unsigned int	message_len;
	int				dest_pid;
	bool			connection;
	bool			busy;
	bool			answerd;
}	t_payload;

t_payload		*get_payload(void);
void			sending_loop(unsigned int what, int bit);
void			sig_connect(int sig);
void			sig_controll(int sig);

// Server

typedef struct s_client
{
	int				pid;
	bool			init;
	int				bit;
	unsigned int	byte;
	unsigned int	what;
	char			*message;
	unsigned int	message_len;
	unsigned long	timeout;
}	t_client;

// server_helper.c

void			interpreter(t_client *client, int signal);
void			add_uint_to_message(unsigned int what, t_client *client);
unsigned long	utime(void);

// server_utils.c

void			delete_client(int index, t_client *clients, int *pids);
void			new_client(int pid, t_client *clients, int *pids, int index);
int				get_index(int pid_looking_for, int *pid_list, bool empty);
t_client		*get_clients(void);
int				*get_pids(void);

#endif
