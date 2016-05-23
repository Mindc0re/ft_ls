#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/18 11:08:40 by sgaudin           #+#    #+#              #
#    Updated: 2016/05/23 12:44:04 by sgaudin          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_ls

CC = gcc -Wall -Wextra -Werror

FLAGS = srcs/flag_fcts/

SRC = srcs/parser.c srcs/main.c srcs/list.c srcs/free_fct.c $(FLAGS)flag_f.c \
	srcs/utils.c

LFT = ./libft/

all: $(NAME)


$(NAME):
	make -C $(LFT)
	$(CC) $(SRC) -o $(NAME) -I./includes -L$(LFT) -lft -L$(LFT) -lftprintf

clean:
	make -C $(LFT) clean

fclean:
	make -C $(LFT) fclean
	rm -rf $(NAME)

re: fclean all
