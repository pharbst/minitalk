/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_minitalk.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 03:21:05 by pharbst           #+#    #+#             */
/*   Updated: 2023/11/11 00:14:43 by pharbst          ###   ########.fr       */
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
void		sending_loop(unsigned int what, int bit);
void		sig_connect(int sig);
void		sig_controll(int sig);

// Server

typedef struct s_busy
{
	bool	flag;
	int		pid;
} t_busy;

typedef struct s_client
{
	int				pid;
	unsigned int	message_len;
	bool			init;
	unsigned int	what;
	int				bit;
	unsigned int	byte;
	char 			*message;
	unsigned long	timeout;
} t_client;

// server_utils.c
void			add_uint_to_message(unsigned int what, t_client *client);
void			pause_client(t_client *client);
unsigned long	utime(void);
int				*get_pids(void);
t_client		*get_clients(void);

// server_helper.c
void			controll_bits(t_client *client, int signal, t_busy *busy);
void			interpreter(t_client *client, int signal, bool controll);
int				get_index(int pid, int pids[256], bool	get_end);
void			new_client(t_client *client, int pid);
void			check_timeout();


#endif