# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    color.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 18:16:49 by pharbst           #+#    #+#              #
#    Updated: 2023/05/03 20:04:01 by pharbst          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# Operating System tracking
# **************************************************************************** #
UNAME		=	$(shell uname)
OS			=	$(shell cat /etc/os-release | grep -e NAME | cut -d= -f2 | tr -d '"')
OS_LIKE		=	$(shell cat /etc/os-release | grep ID_LIKE | cut -d= -f2)


ifeq ($(UNAME), Darwin)
# ****************************************************************************  #
# Colors and Printing stuff
# ****************************************************************************  #
Black			=	$(shell echo "\033[0;30m")
FBlack			=	$(shell echo "\033[1;30m")
Red				=	$(shell echo "\033[0;31m")
FRed			=	$(shell echo "\033[1;31m")
Green			=	$(shell echo "\033[0;32m")
FGreen			=	$(shell echo "\033[1;32m")
FYellow			=	$(shell echo "\033[1;33m")
Yellow			=	$(shell echo "\033[0;33m")
Blue			=	$(shell echo "\033[0;34m")
FBlue			=	$(shell echo "\033[1;34m")
Purple			=	$(shell echo "\033[0;35m")
FPurple			=	$(shell echo "\033[1;35m")
Cyan			=	$(shell echo "\033[0;36m")
FCyan			=	$(shell echo "\033[1;36m")
FWhite			=	$(shell echo "\033[1;37m")
White			=	$(shell echo "\033[0;37m")
RESET			=	$(shell echo "\033[0m")

TICK			=	$(shell echo "\xE2\x9C\x94")
TICKBOX			=	$(shell echo "[$(TICK)]")
SCHMILI			=	$(shell echo "☺")

SETCURSTART		=	$(shell echo "\r")
SETCURUP		=	$(shell echo "\033[1A")
SETCURDOWN		=	$(shell echo "\033[1B")
CLEARLINE		=	$(shell echo "\033[2K")
else
# ****************************************************************************  #
# Colors and Printing stuff
# ****************************************************************************  #
Black			=	$(shell echo -e "\033[0;30m")
FBlack			=	$(shell echo -e "\033[1;30m")
Red				=	$(shell echo -e "\033[0;31m")
FRed			=	$(shell echo -e "\033[1;31m")
Green			=	$(shell echo -e "\033[0;32m")
FGreen			=	$(shell echo -e "\033[1;32m")
FYellow			=	$(shell echo -e "\033[1;33m")
Yellow			=	$(shell echo -e "\033[0;33m")
Blue			=	$(shell echo -e "\033[0;34m")
FBlue			=	$(shell echo -e "\033[1;34m")
Purple			=	$(shell echo -e "\033[0;35m")
FPurple			=	$(shell echo -e "\033[1;35m")
Cyan			=	$(shell echo -e "\033[0;36m")
FCyan			=	$(shell echo -e "\033[1;36m")
FWhite			=	$(shell echo -e "\033[1;37m")
White			=	$(shell echo -e "\033[0;37m")
RESET			=	$(shell echo -e "\033[0m")

TICK			=	$(shell echo -e "\xE2\x9C\x94")
TICKBOX			=	$(shell echo -e "[\xE2\x9C\x94]")
SCHMILI			=	$(shell echo -e "☺")

SETCURSTART		=	$(shell echo -e "\r")
SETCURUP		=	$(shell echo -e "\033[1A")
SETCURDOWN		=	$(shell echo -e "\033[1B")
CLEARLINE		=	$(shell echo -e "\033[2K")
endif