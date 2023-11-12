# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/22 14:24:08 by pharbst           #+#    #+#              #
#    Updated: 2023/11/12 03:44:45 by pharbst          ###   ########.fr        #
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
HEADER	:=	./includes/new_minitalk.h
ifeq ($(UNAME), Darwin)
LIBS	:=	$(LIBFT)/libftio.a
else
LIBS	:=	$(LIBFT)/libftio_linux.a
endif

INC		:=	-I ./includes -I $(LIBFT)/includes
VPATH	:=	src src/client src/server

S_SRCS	:=	new_server.c \
			new_server_helper.c \
			new_server_utils.c

C_SRCS	:=	new_client.c \
			new_client_helper.c

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
	@printf "%-67s$(RESET)" "$(Yellow)Updating $(FCyan)submodule ..."
	@git submodule update --init >/dev/null 2>&1
endif
	@printf "$(FGreen)[$(TICK)]\n$(RESET)"
	@printf "%-67s$(RESET)" "$(Yellow)Compiling $(FCyan)libft ..."
	@./spinner.sh $(MAKE) -j -s -C $(LIBFT) >/dev/null
	@printf "$(FGreen)[$(TICK)]\n$(RESET)"
	@printf "%-67s$(RESET)" "$(Yellow)Compiling $(FCyan)$(NAME) ..."	
	@./spinner.sh $(MAKE) -s $(NAME)
	@printf "$(FGreen)[$(TICK)]\n$(RESET)"

bonus:
	@$(MAKE) -s proname_header
	@$(MAKE) -s std_bonus

std_bonus:
ifneq ($($(LIBFT)/Makefile), "")
	@printf "%-67s$(RESET)" "$(Yellow)Updating $(FCyan)submodule ..."
	@git submodule update --init >/dev/null 2>&1
endif
	@printf "$(FGreen)[$(TICK)]\n$(RESET)"
	@printf "%-67s$(RESET)" "$(Yellow)Compiling $(FCyan)libft ..."
	@./spinner.sh $(MAKE) -j -s -C $(LIBFT) >/dev/null
	@printf "$(FGreen)[$(TICK)]\n$(RESET)"
	@./spinner.sh $(MAKE) -s $(NAME)

$(NAME): 
	@printf "\n%-67s$(RESET)" "$(Yellow)Compiling $(FCyan)Server ..."
	@$(MAKE) -s server
	@printf "$(FGreen)[$(TICK)]\n$(RESET)"
	@printf "%-67s$(RESET)" "$(Yellow)Compiling $(FCyan)Client ..."
	@$(MAKE) -s client
	@printf "$(FGreen)[$(TICK)]$(RESET)"

server: $(ODIR) $(S_OBJS)
	@$(CC) $(CFLAGS) $(S_OBJS) $(LIBS) $(INC) -o $@

client: $(ODIR) $(C_OBJS)
	@$(CC) $(CFLAGS) $(C_OBJS) $(LIBS) $(INC) -o $@

$(ODIR)/%.o: %.c $(HEADER) | $(ODIR)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(ODIR):
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
	@printf "%-60s$(RESET)" "$(FPurple)Cleaning up ..."
	@$(RM) -rf $(ODIR)
	@printf "$(FGreen)$(TICKBOX)\n$(RESET)"

fclean:	libft
	@$(MAKE) -s proname_header
	@$(MAKE) -s cleanator

cleanator:
	@printf "%-60s$(RESET)" "$(FPurple)FCleaning up ..."
	@$(RM) -rf $(ODIR)
	@$(RM) -rf $(NAME)
	@printf "$(FGreen)$(TICKBOX)\n$(RESET)"

re:
	@$(MAKE) -s proname_header
	@$(MAKE) -s cleanator
	@$(MAKE) -s std_all

# **************************************************************************** #
# Header Rules                                                                 #
# **************************************************************************** #

proname_header:
	@printf "$(FCyan)╔══════════════════════════════════════════════════════╗$(RESET)\n\
$(FCyan)║$(FPurple)  _____           _        _____                      $(FCyan)║\n\
$(FCyan)║$(FPurple) |  __ \\         | |      / ____|                     $(FCyan)║\n\
$(FCyan)║$(FPurple) | |__) |   _ ___| |__   | (_____      ____ _ _ __    $(FCyan)║\n\
$(FCyan)║$(FPurple) |  ___/ | | / __| \'_ \\   \\___ \\ \\ /\\ / / _\` | \'_ \\   $(FCyan)║\n\
$(FCyan)║$(FPurple) | |   | |_| \\__ \\ | | |  ____) \\ V  V / (_| | |_) |  $(FCyan)║\n\
$(FCyan)║$(FPurple) |_|    \\__,_|___/_| |_| |_____/ \\_/\\_/ \\__,_| .__/   $(FCyan)║\n\
$(FCyan)║$(FPurple)                     ______                  | |      $(FCyan)║\n\
$(FCyan)║$(FPurple)                    |______|                 |_|      $(FCyan)║\n\
$(FCyan)╚══════════════════════════════════════════════════════╝\n$(RESET)"
