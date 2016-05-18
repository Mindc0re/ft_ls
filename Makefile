#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/18 11:08:40 by sgaudin           #+#    #+#              #
#    Updated: 2016/05/18 11:14:41 by sgaudin          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_ls

CC = gcc -Wall -Wextra -Werror

SRC = srcs/parser.c srcs/main.c

LFT = ./libft/

all: $(NAME)


$(NAME):
	make -C $(LFT)
	$(CC) $(SRC) -o $(NAME) -I./includes -L$(LFT) -lft

clean:
	make -C $(LFT) clean

fclean:
	make -C $(LFT) fclean
	rm -rf $(NAME)

re: fclean all