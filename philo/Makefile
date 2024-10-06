# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: timanish <timanish@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/30 15:54:45 by timanish          #+#    #+#              #
#    Updated: 2024/09/30 15:55:42 by timanish         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFRAGS = -Wall -Wextra -Werror
NAME = philo.a
SRCS = 	\


OBJS = $(SRCS:.c=.o)

OBJSB = $(SRCSB:.c=.o)

INCLUDES = -I includes

$(NAME) :    $(OBJS)
	ar rc $(NAME) $(OBJS)

%.o:%.c
	$(CC) -c  $(CFLAGS) $^ -o $@ $(INCLUDES)

all : $(NAME)
	
clean :
	rm -f $(OBJS) $(OBJSB)

fclean : clean
	rm -f $(NAME)

re : fclean all 

.PHONY : all clean fclean re