# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/05 14:59:53 by ohladkov          #+#    #+#              #
#    Updated: 2024/03/10 14:17:13 by ohladkov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
SRCS	= philo.c philo_utils.c is_valid.c print_err.c fork_utils.c actions.c \
			init_data.c
OBGS	= $(SRCS:.c=.o)

CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Werror -Wextra -g
#-fsanitize=thread
#valgrind --tool=helgrind  

all:	$(NAME)

$(NAME):	$(OBGS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

run: ./philo 7 800 300 200 2

clean:
	$(RM) *.o

fclean:	clean
	$(RM) $(NAME)

re:	fclean all
