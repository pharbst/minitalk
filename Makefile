# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/19 18:08:33 by pharbst           #+#    #+#              #
#    Updated: 2023/11/11 00:38:48 by pharbst          ###   ########.fr        #
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

NAME		:= server

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
VPATH		:=	src src/server src/client

SRC			:=	new_server.c \
				new_server_helper.c \
				new_server_utils.c

ODIR		:=	obj
OBJS		:=	$(SRCS_SERVER:%.c=$(ODIR)/%.o)

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
ifneq ($($(LIBFT)/Makefile), "")
	@printf "%-64s$(RESET)" "$(Yellow)Updating $(FCyan)submodule ..."
	@git submodule update --init >/dev/null 2>&1
endif
	@printf "$(FGreen)[$(TICK)]\n$(RESET)"
	@printf "%-64s$(RESET)" "$(Yellow)Compiling $(FCyan)libft ..."
	@./spinner.sh $(MAKE) -j -s -C $(LIBFT) >/dev/null
	@printf "$(FGreen)[$(TICK)]\n$(RESET)"
	@printf "%-64s$(RESET)" "$(Yellow)Compiling $(FCyan)$(NAME) ..."	
	@./spinner.sh $(MAKE) -s $(NAME)
	@printf "$(FGreen)[$(TICK)]\n$(RESET)"

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(INC) -o $(NAME)
	

$(ODIR)/%.o: %.c $(HEADER) | $(ODIR)
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