# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pharbst <pharbst@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/22 14:24:08 by pharbst           #+#    #+#              #
#    Updated: 2023/11/16 11:06:36 by pharbst          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include color.mk

# **************************************************************************** #
# Variables
# **************************************************************************** #

NAME	:=	minitalk

CC		:=	cc
CFLAGS	:=	-Wextra -Wall -Werror
# CFLAGS	:=	-Wall -Werror -Wextra -Wunreachable-code -g
# CFLAGS	+=	-fsanitize=address

LIBFT	:=	./libft
HEADER	:=	./includes/minitalk.h
ifeq ($(UNAME), Darwin)
LIBS	:=	$(LIBFT)/libftio.a
else
LIBS	:=	$(LIBFT)/libftio_linux.a
endif

INC		:=	-I ./includes -I $(LIBFT)/includes
VPATH	:=	src src/client src/server

S_SRCS	:=	server.c \
			server_helper.c \
			server_utils.c

C_SRCS	:=	client.c \
			client_helper.c

ODIR	:=	obj

S_OBJS	:=	$(S_SRCS:%.c=$(ODIR)/%.o)
C_OBJS	:=	$(C_SRCS:%.c=$(ODIR)/%.o)

# **************************************************************************** #
# Compilation Rules
# **************************************************************************** #

all:
	@$(MAKE) -s proname_header
	@$(MAKE) -s std_all
	
std_all:
ifneq ($($(LIBFT)/Makefile), "")
	@printf "%-71s$(RESET)" "$(Yellow)Updating $(FCyan)submodule ..."
	@git submodule update --init >/dev/null 2>&1
endif
	@printf "$(FGreen)[$(TICK)]\n$(RESET)"
	@printf "%-71s$(RESET)" "$(Yellow)Compiling $(FCyan)libft ..."
	@./spinner.sh $(MAKE) -j -s -C $(LIBFT) >/dev/null
	@printf "$(FGreen)[$(TICK)]\n$(RESET)"	
	@./spinner.sh $(MAKE) -s $(NAME)

$(NAME): 
	@printf "%-71s\n$(RESET)" "$(Yellow)Compiling $(FCyan)Server ..."
	@$(MAKE) -s server
	@printf "$(CLEARLINE)"
	@printf "$(SETCURUP)"
	@printf "%-71s$(RESET)" "$(Yellow)Compiling $(FCyan)Server ..."
	@printf "$(FGreen)[$(TICK)]\n$(RESET)"
	@printf "%-71s\n$(RESET)" "$(Yellow)Compiling $(FCyan)Client ..."
	@$(MAKE) -s client
	@printf "$(CLEARLINE)"
	@printf "$(SETCURUP)"
	@printf "%-71s$(RESET)" "$(Yellow)Compiling $(FCyan)Client ..."
	@printf "$(FGreen)[$(TICK)]\n$(RESET)"

server: $(ODIR) $(S_OBJS)
	@$(CC) $(CFLAGS) $(S_OBJS) $(LIBS) $(INC) -o $@

client: $(ODIR) $(C_OBJS)
	@$(CC) $(CFLAGS) $(C_OBJS) $(LIBS) $(INC) -o $@

$(ODIR)/%.o: %.c $(HEADER) | $(ODIR)
	@printf "%-50s$(RESET)\r" "$(Green)Compiling $< ..."
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(ODIR):
	@printf "$(CLEARLINE)$(SETCURSTART)$(Yellow)Creating objectdirectory ..."
	@mkdir -p $@

libft:
	@$(MAKE) -j -s -C $(LIBFT) $(MAKECMDGOALS) >/dev/null

# **************************************************************************** #
# Cleaning Rules
# **************************************************************************** #

clean:	libft
	@$(MAKE) -s proname_header
	@$(MAKE) -s std_clean

std_clean:
	@printf "%-64s$(RESET)" "$(FPurple)Cleaning up ..."
	@$(RM) -rf $(ODIR)
	@printf "$(FGreen)$(TICKBOX)\n$(RESET)"

fclean:	libft
	@$(MAKE) -s proname_header
	@$(MAKE) -s cleanator

cleanator:
	@printf "%-64s$(RESET)" "$(FPurple)FCleaning up ..."
	@$(RM) -rf $(ODIR)
	@$(RM) -rf server client
	@printf "$(FGreen)$(TICKBOX)\n$(RESET)"

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
