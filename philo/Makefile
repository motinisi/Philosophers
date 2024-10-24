# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: timanish <timanish@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/30 15:54:45 by timanish          #+#    #+#              #
#    Updated: 2024/10/24 17:57:51 by timanish         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFRAGS = -Wall -Wextra -Werror
NAME = philo
SRCS = 	main.c\
		ft_atoi.c\
		philo_thread.c\
		routine.c\

OBJS = $(SRCS:.c=.o)

INCLUDES = -I includes

all : $(NAME)

$(NAME) :    $(OBJS)
	$(CC) $(OBJS) -o $(NAME)
%.o:%.c
	$(CC) $(INCLUDES) -c  $(CFLAGS) $< -o $@
	
clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all 

.PHONY : all clean fclean re