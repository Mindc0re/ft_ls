#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/18 11:08:40 by sgaudin           #+#    #+#              #
#    Updated: 2016/06/10 10:14:02 by sgaudin          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_ls

CC = gcc -Wall -Wextra -Werror

SRC = srcs/parser.c srcs/main.c srcs/list.c srcs/free_fct.c	srcs/utils.c \
	srcs/stats.c srcs/read_dir.c srcs/tri_file.c srcs/print.c

LFT = ./libft/

all: $(NAME)


$(NAME):
	make -C $(LFT)
	$(CC) $(SRC) -o $(NAME) -I./includes -L$(LFT) -lft -L$(LFT) -L$(LFT)/ft_printf/ -lftprintf

clean:
	make -C $(LFT) clean

fclean:
	make -C $(LFT) fclean
	rm -rf $(NAME)

re: fclean all
