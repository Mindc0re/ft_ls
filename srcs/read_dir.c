/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 09:31:59 by sgaudin           #+#    #+#             */
/*   Updated: 2016/06/09 09:55:15 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		print_list(t_all *all)
{
	if (all->list_bis)
	{
		backlist(all, W_FILE, &all->list_bis);
		while (all->list_bis->next)
		{
			ft_printf("%s ", all->list_bis->name);
			all->list_bis = all->list_bis->next;
		}
		ft_printf("%s\n", all->list_bis->name);
		free_list(all, &all->list_bis);
	}
	if (all->list)
	{
		backlist(all, W_FILE, &all->list);
		if (ft_strcmp("./", all->args->name) && all->ac >= 3)
			ft_printf("\n%s:\n\n", all->args->name);
		while (all->list->next)
		{
			if (all->list->name[0] == '.')
			{
				if (all->flag_a)
					ft_printf("%s ", all->list->name);
			}
			else
				ft_printf("%s ", all->list->name);
			all->list = all->list->next;
		}
		ft_printf("%s\n", all->list->name);
	}
}

/*
void		create_args_spec(t_all *all, char *str)
{
	t_dir	*new;
	static	t_dir **last = NULL;

	new = init_list();
	new->name = ft_strnew(ft_strlen(str));
	new->name = str;
	if (last)
	{
		(*last) = (*last)->next;
		new->prev = (*last);
		new->next = (*last)->next;
		(*last)->next = new;
		(*last) = (*last)->next;
	}
	else
	{
		new->prev = all->args;
		new->next = all->args->next;
		all->args->next = new;
		last = &all->args;
	}
}
*/
void		flag_r_detect(t_all *all)
{
	char *tmp_path;

	tmp_path = NULL;
//	backlist(all, W_FILE, &all->list);
	if (all->flag_r_big)
	{
		while (all->list)
		{
			if (all->list->type == T_DIR && ft_strcmp(".", all->list->name) && ft_strcmp("..", all->list->name))
			{
				tmp_path = ft_strcmp(all->args->name, "./") ? ft_strjoin(all->args->name, "/") : ft_strdup("./");
				all->ac++;
				create_args(all, ft_strjoin(tmp_path, all->list->name), 0);
				free(tmp_path);
			}
			if (all->list->prev)
				all->list = all->list->prev;
			else
				break ;
		}
	}
}

/*
void		flag_r_detect(t_all *all, struct dirent **file)
{
	char *tmp_path;

	tmp_path = NULL;
	if (all->list)
	{
		if (all->flag_r_big && !(ft_strcmp(all->list->name, (*file)->d_name)))
		{
			if (all->list->type == T_DIR && ft_strcmp(".", (*file)->d_name) && ft_strcmp("..", (*file)->d_name))
			{
				tmp_path = ft_strjoin(all->args->name, "/");
				all->ac++;
				create_args(all, ft_strjoin(tmp_path, (*file)->d_name), 0);
				free(tmp_path);
			}
		}
	}
}
*/
void		read_dir(t_all *all, char *str)
{
	DIR				*dir;
	struct dirent	*file;
	struct stat		stats;

	dir = opendir(str);
	while ((file = readdir(dir)))
	{
		stat(file->d_name, &stats);
		if (file->d_name[0] == '.')
		{
			if (all->flag_a)
				create_list(file->d_name, &all->list, all);
		}
		else
			create_list(file->d_name, &all->list, all);
	}
	tri_lst(&all->list, all);
	flag_r_detect(all);
	closedir(dir);
}
