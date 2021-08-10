# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anadege <anadege@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/10 21:19:50 by anadege           #+#    #+#              #
#    Updated: 2021/08/10 21:35:14 by anadege          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ./main.c \
		  ./parsing.c \
		  ./init_philo.c \
		  ./scripts.c \
		  ./actions.c \
		  ./checks.c \
		  ./utils.c

NAME = philo

CC	= cc

CFLAGS	= -Wall -Wextra -Werror

OBJS	= ${SRCS:.c=.o}

LIB		= -lpthread

%.o: %.c
			${CC} -g ${CFLAGS} -o $@ -c $<

all:		${NAME}
			@echo "\n\tWelcome to philosphers project !\n"
			@echo "Philosphers are around a table and can either think, sleep or eat.\n"
			@echo "There is a big bowl of spaghettis in the center of the table.\n"
			@echo "Because it's difficult to eat, they need two forks.\n"
			@echo "There's as many forks as philosphers, each fork between two philosphers and accessible only to those two.\n'"
			@echo "If they don't eat after a certain time lapse, they die.\n"
			@echo "Watch them by launching ./philo\n"
			@echo "\n\tYou have to precise :\n"
			@echo "- The number of philosophers\n"
			@echo "- The time in milliseconds between two meals before they die\n"
			@echo "- The time in milliseconds they take to eat\n"
			@echo "- The time in milliseconds they take to sleep after eating\n"
			@echo "- Additionnal : The number of meals each philosopher must have to end the simulation\n"
			@echo "\n\tHave fun !!!\n"

${NAME}:	${OBJS}
			${CC} -o ${NAME} ${OBJS} ${LIB}

clean:
			@rm -f ${OBJS}

fclean: 	clean
			@rm -f ${NAME}

re:			fclean all

.PHONY: all clean re
