/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 09:31:59 by sgaudin           #+#    #+#             */
/*   Updated: 2016/06/09 17:37:09 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		print_list_hub(t_all *all)
{
	if (all->list_bis)
		print_list_bis(all);
	print_list_reg(all);
}

void		flag_r_detect(t_all *all)
{
	char *tmp_path;

	tmp_path = NULL;
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
	if (!all->flag_f)
		tri_lst(&all->list, all);
	flag_r_detect(all);
	get_total_blocks(all);
	closedir(dir);
}
