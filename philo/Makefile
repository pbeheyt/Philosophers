# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 15:08:45 by pbeheyt           #+#    #+#              #
#    Updated: 2022/10/18 22:09:02 by pbeheyt          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRC		= main.c \
		clear.c \
		error.c \
		init.c \
		libft.c \
		routine.c \
		solve.c \
		utilis.c \

DIR 	= ${addprefix srcs/,${SRC}}

HEAD	= -I include

CC 		= gcc

CFLAGS 	= -Wall -Wextra -Werror -g -pthread #-fsanitize=thread

OBJS 	= ${DIR:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)


.c.o:
	${CC} ${CFLAGS} ${HEAD} -c $< -o ${<:.c=.o}

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
