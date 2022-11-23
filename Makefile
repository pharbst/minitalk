# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/19 18:08:33 by pharbst           #+#    #+#              #
#    Updated: 2022/11/23 19:30:32 by pharbst          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = server client

SRC = server.c client.c client_help.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): client server

server: $(OBJ) libftio
	$(CC) $(CFLAGS) $@.o -L libft/ -lftio -o $@

client: $(OBJ) libftio
	$(CC) $(CFLAGS) $@.o client_help.o -L libft/ -lftio -o $@

libftio:
	make -C libft

clean:
	rm -f $(OBJ)
	make clean -C libft

fclean:
	rm -f server client $(OBJ)
	make fclean -C libft

re: fclean all