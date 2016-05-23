/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 10:37:52 by sgaudin           #+#    #+#             */
/*   Updated: 2016/05/23 10:27:54 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		parse_flag(char *str, t_all *all)
{
	FT_INIT(int, i, 1);
	while (str[i])
	{
		all->flag_R = (str[i] == 'R') ? 1 : all->flag_R;
		all->flag_t = (str[i] == 't') ? 1 : all->flag_t;
		all->flag_a = (str[i] == 'a') ? 1 : all->flag_a;
		all->flag_r = (str[i] == 'r') ? 1 : all->flag_r;
		all->flag_l = (str[i] == 'l') ? 1 : all->flag_l;
		if (!ft_strchr("Rratl", str[i]))
		{
			ft_printf("ft_ls : illegal option -- %c\n", str[i]);
			ft_printf("Avalaible options : [atlRr]\n");
			free_list(all);
			free(all);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
}

void			parser_ls(char **av, t_all *all)
{
	FT_INIT(int, i, 1);
	if (all->ac == 1)
		ft_printf("Lecture du repertoire courant\n");
	else
	{
		ft_printf("Parsing des arguments\n");
		while (i < all->ac)
		{
			if (av[i][0] == '-')
				parse_flag(av[i], all);
			else
				ft_printf("File or directory : %s\n", av[i]);
			i++;
		}
	}
}
