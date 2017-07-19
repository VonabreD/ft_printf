#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ederbano <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/25 02:46:37 by ederbano          #+#    #+#              #
#    Updated: 2017/05/15 15:38:15 by ederbano         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = 'libftprintf.a'

CC = gcc

SRC = data_proc_hh.c data_proc_l.c ft_printf.c  param_parce.c data_proc.c data_proc_o.c data_proc_h.c ft_atoi.c ft_isdigit.c ft_putchar.c ft_putstr.c ft_strlen.c ft_isalpha.c

SRCO = $(SRC:.c=.o)

INCLUDES = ft_printf.h

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRCO)
		$(CC) $(FLAGS) -I $(INCLUDES) -c $(SRC)
		ar rc $(NAME) $(SRCO)
		ranlib $(NAME)

.c.o:
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(SRCO)

fclean: clean
	rm -f $(NAME)
re: fclean all