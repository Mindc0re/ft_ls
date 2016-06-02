/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 10:37:52 by sgaudin           #+#    #+#             */
/*   Updated: 2016/06/02 10:07:11 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		parse_flag(char *str, t_all *all)
{
	FT_INIT(int, i, 1);
	while (str[i])
	{
		all->flag_r_big = (str[i] == 'R') ? 1 : all->flag_r_big;
		all->flag_t = (str[i] == 't') ? 1 : all->flag_t;
		all->flag_a = (str[i] == 'a') ? 1 : all->flag_a;
		all->flag_r = (str[i] == 'r') ? 1 : all->flag_r;
		all->flag_l = (str[i] == 'l') ? 1 : all->flag_l;
		all->flag_f = (str[i] == 'f') ? 1 : all->flag_f;
		if (!ft_strchr("Rratlf", str[i]))
		{
			ft_printf("ft_ls : illegal option -- %c\n", str[i]);
			ft_printf("Avalaible options : [atlRrf]\n");
			free_args(all);
			free(all);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
}

void			choice_flag(t_all *all)
{
	if (all->flag_f)
		flag_f(all);
}

void			parser_ls(t_all *all)
{
	struct stat		stats;
	DIR				*dir;
	struct dirent	file;
	int				ret;

	while (all->args)
	{
		free_list(all);
		if (!(dir = opendir(all->args->name)))
		{
			if ((ret = stat(all->args->name, &file)) == -1 || S_ISDIR(file.st_mode))
			{
				ft_printf("%s: ", all->args->name);
				perror("ft_ls");
			}
		}
		else
			// FAIRE LA BOUCLE DU READDIR QUI VA LIRE TOUT CE DONT ON A BESOIN
		all->args = all->args->next;
	}
}

void			parser_args(char **av, t_all *all)
{
	int check = 0;

	FT_INIT(int, i, 1);
	while (i < all->ac)
	{
		if (av[i][0] == '-')
			parse_flag(av[i], all);
		else
		{
			create_args(all, av[i]);
			check++;
		}
		i++;
	}
	if (check == 0)
		create_args(all, "./");
	parser_ls(all);
	choice_flag(all);
}
