# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohladkov <ohladkov@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/05 14:59:53 by ohladkov          #+#    #+#              #
#    Updated: 2024/03/09 23:31:14 by ohladkov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
SRCS	= *.c
#SRCS	= philo.c ft_atoi.c ft_split.c print_err.c
OBGS	= $(SRCS:.c=.o)

CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Werror -Wextra -g
#-g -fsanitize=thread
#valgrind --tool=helgrind

all:	$(NAME)

$(NAME):	$(OBGS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


run:
	./philo 7 310 200 100
 
clean:
	$(RM) *.o

fclean:	clean
	$(RM) $(NAME)

re:	fclean all
