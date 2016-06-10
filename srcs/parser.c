/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 10:37:52 by sgaudin           #+#    #+#             */
/*   Updated: 2016/06/10 13:47:47 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		create_list_spec(char *str, t_files **list, t_all *all)
{
	t_files		*new;
	struct stat	file;

	if (!(*list))
	{
		(*list) = init_file();
		(*list)->name = str;
		lstat((*list)->name, &file);
		get_type(&(*list), &file, all);
	}
	else
	{
		new = init_file();
		new->name = str;
		lstat(new->name, &file);
		get_type(&new, &file, all);
		new->prev = (*list);
		(*list)->next = new;
		(*list) = (*list)->next;
	}
}

static void		first_parse(t_all *a)
{
	struct stat		s;
	DIR				*dir;
	int				ret;

	backlist(&a->args);
	while (a->args)
	{
		if (!(dir = opendir(a->args->name)))
		{
			if ((ret = lstat(a->args->name, &s)) == 0 && !(S_ISDIR(s.st_mode)))
				create_list_spec(a->args->name, &a->list_bis, a);
			else
			{
				ft_printf("%s: ", a->args->name);
				perror("ft_ls");
			}
		}
		if (a->args->next)
			a->args = a->args->next;
		else
			break ;
	}
	if (!a->flag_f)
		tri_lst(&a->list_bis, a);
	print_list_hub(a);
}

static void		parse_flag(char *str, t_all *all)
{
	FT_INIT(int, i, 1);
	while (str[i])
	{
		all->flag_r_big = (str[i] == 'R') ? 1 : all->flag_r_big;
		all->flag_t = (str[i] == 't') ? 1 : all->flag_t;
		all->flag_a = (str[i] == 'a') || (str[i] == 'f') ? 1 : all->flag_a;
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

void			parser_ls(t_all *a)
{
	DIR				*dir;

	backlist(&a->args);
	while (a->args)
	{
		free_list(&a->list);
		if ((dir = opendir(a->args->name)))
		{
			closedir(dir);
			read_dir(a, a->args->name);
			print_list_hub(a);
		}
		if (a->args->next)
			a->args = a->args->next;
		else
			break ;
	}
}

void			parser_args(char **av, t_all *all)
{
	FT_INIT(int, check, 0);
	FT_INIT(int, i, 1);
	while (i < all->ac)
	{
		if (av[i][0] == '-')
			parse_flag(av[i], all);
		else
		{
			create_args(all, av[i], 1);
			check++;
		}
		i++;
	}
	if (check == 0)
		create_args(all, "./", 1);
	tri_lst(&all->args, all);
	backlist(&all->args);
	first_parse(all);
	parser_ls(all);
}
