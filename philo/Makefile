# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohladkov <ohladkov@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/05 14:59:53 by ohladkov          #+#    #+#              #
#    Updated: 2024/03/07 22:21:34 by ohladkov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
SRCS	= *.c
#SRCS	= philo.c ft_atoi.c ft_split.c print_err.c
OBGS	= $(SRCS:.c=.o)

CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Werror -Wextra -g
# -pthread
#-g -fsanitize=thread
#-g -fsanitize=address
#valgrind --tool=helgrind

all:	$(NAME)

$(NAME):	$(OBGS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# valgrind --tool=helgrind ./philo 5 800 200 200
run:
	valgrind --tool=helgrind ./philo 5 800 200 200

clean:
	$(RM) *.o

fclean:	clean
	$(RM) $(NAME)

re:	fclean all
