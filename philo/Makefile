# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: timanish <timanish@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/30 15:54:45 by timanish          #+#    #+#              #
#    Updated: 2024/12/25 14:47:22 by timanish         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -ggdb
NAME = philo
SRCS = 	main.c\
		ft_atoi.c\
		philo_thread.c\
		routine.c\
		monitor.c\
		philo_utils.c\

OBJS = $(SRCS:.c=.o)

INCLUDES = -I includes

all : $(NAME)

$(NAME) :    $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)
%.o:%.c
	$(CC) $(INCLUDES) -c  $(CFLAGS) $< -o $@
	
clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all 

.PHONY : all clean fclean re
