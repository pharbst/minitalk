# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/19 18:08:33 by pharbst           #+#    #+#              #
#    Updated: 2023/11/11 03:59:43 by pharbst          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# Operating System tracking
# **************************************************************************** #
UNAME		=	$(shell uname)
OS			=	$(shell cat /etc/os-release | grep -e NAME | cut -d= -f2 | tr -d '"')
OS_LIKE		=	$(shell cat /etc/os-release | grep ID_LIKE | cut -d= -f2)

include color.mk

# **************************************************************************** #
# Variables
# **************************************************************************** #

NAME		:=	server

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
# CFLAGS		:=	-Wall -Werror -Wextra -Wunreachable-code -g
# CFLAGS		+=	-fsanitize=address

LIBFT		:=	./libft
HEADER		:=	./new_minitalk.h
ifeq ($(UNAME), Darwin)
LIBS		:=	$(LIBFT)/libftio.a
else
LIBS		:=	$(LIBFT)/libftio_linux.a
endif

INC			:=	-I ./includes -I $(LIBFT)/includes
VPATH		:=	src ./src/server ./src/client

server_src	:=	new_server.c \
				new_server_helper.c \
				new_server_utils.c

client_src	:=	new_client.c \
				new_client_helper.c

ODIR		:=	./obj

server_obj	:=	$(addprefix $(ODIR)/, $(server_src:.c=.o))
# server_obj	:=	$(server_src:%.c=$(ODIR)/%.o)
client_obj	:=	$(client_src:%.c=$(ODIR)/%.o)

# **************************************************************************** #
# Compilation Rules
# **************************************************************************** #

all:
	@$(MAKE) -s proname_header
	@$(MAKE) -s std_all
# **************************************************************************** #
# Compilation Rules
# **************************************************************************** #

std_all:
ifeq ($($(LIBFT)/Makefile), "")
	@printf "%-64s$(RESET)" "$(Yellow)Updating $(FCyan)submodule ..."
	@git submodule update --init >/dev/null 2>&1
	@printf "$(FGreen)[$(TICK)]\n$(RESET)"
endif
	@printf "%-71s$(RESET)" "$(Yellow)Compiling $(FCyan)libft ..."
	@./spinner.sh $(MAKE) -j -s -C $(LIBFT) >/dev/null
	@printf "$(FGreen)[$(TICK)]\n$(RESET)"
	@printf "%-64s$(RESET)" "$(Yellow)Compiling $(FCyan)server ..."	
	@./spinner.sh $(MAKE) -s server
	@printf "$(FGreen)[$(TICK)]\n$(RESET)"
	@printf "%-64s$(RESET)" "$(Yellow)Compiling $(FCyan)client ..."	
	@./spinner.sh $(MAKE) -s client
	@printf "$(FGreen)[$(TICK)]\n$(RESET)"

server: $(ODIR) $(server_obj)
	@echo "$(CC) $(CFLAGS) $(server_obj) $(LIBS) $(INC) -o $@"
	$(CC) $(CFLAGS) $(server_obj) $(LIBS) $(INC) -o $@

client: $(client_obj)
	@echo "$(CC) $(CFLAGS) $(client_obj) $(LIBS) $(INC) -o $@"
	$(CC) $(CFLAGS) $(client_obj) $(LIBS) $(INC) -o $@
	

$(ODIR)/%.o : %.c $(HEADER) | $(ODIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(ODIR):
	mkdir -p $@

libft:
	@$(MAKE) -j -s -C $(LIBFT) $(MAKECMDGOALS) >/dev/null

# **************************************************************************** #
# Cleaning Rules                                                               #
# **************************************************************************** #

clean:	libft
	@$(MAKE) -s proname_header
	@$(MAKE) -s std_clean

std_clean:
	@printf "%-64s$(RESET)" "$(Yellow)Cleaning up..."
	@$(RM) -rf $(ODIR)
	@printf "$(FGreen)[$(TICK)]\n$(RESET)"

fclean: libft
	@$(MAKE) -s proname_header
	@$(MAKE) -s cleanator

cleanator:
	@printf "%-64s$(RESET)" "$(Yellow)FCleaning up..."
	@$(RM) -rf $(ODIR)
	@$(RM) -rf $(NAME)
	@printf "$(FGreen)[$(TICK)]\n$(RESET)"

re:
	@$(MAKE) -s proname_header
	@$(MAKE) -s cleanator
	@$(MAKE) -s std_all


# **************************************************************************** #
# Header Rules                                                                 #
# **************************************************************************** #

proname_header:
	@printf "$(FCyan)╔══════════════════════════════════════════════════════════╗$(RESET)\n\
$(FCyan)║ $(FPurple)           _       _                                     $(FCyan)║\n\
$(FCyan)║ $(FPurple)          (_)     (_)   ████████  █████  ██      ██   ██ $(FCyan)║\n\
$(FCyan)║ $(FPurple) _ __ ___  _ _ __  _       ██    ██   ██ ██      ██  ██  $(FCyan)║\n\
$(FCyan)║ $(FPurple)| \'_ \` _ \\| | \'_ \\| |      ██    ███████ ██      █████   $(FCyan)║\n\
$(FCyan)║ $(FPurple)| | | | | | | | | | |      ██    ██   ██ ██      ██  ██  $(FCyan)║\n\
$(FCyan)║ $(FPurple)|_| |_| |_|_|_| |_|_|      ██    ██   ██ ███████ ██   ██ $(FCyan)║\n\
$(FCyan)╚══════════════════════════════════════════════════════════╝\n$(RESET)"

.PHONY: all std_all $(NAME) server client libft clean fclean re std_clean cleanator