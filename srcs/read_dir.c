/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 09:31:59 by sgaudin           #+#    #+#             */
/*   Updated: 2016/06/06 12:51:54 by sgaudin          ###   ########.fr       */
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
			ft_printf("%s ", all->list->name);
			all->list = all->list->next;
		}
		ft_printf("%s\n", all->list->name);
	}
}

void		read_dir(t_all *all, char *str)
{
	DIR				*dir;
	struct dirent	*file;
	struct stat		stats;
	char			*tmp_path;

	dir = opendir(str);
	tmp_path = NULL;
	while ((file = readdir(dir)))
	{
		stat(file->d_name, &stats);
		create_list(file->d_name, &all->list, all);
		if (all->flag_r_big)
		{
			if (all->list->type == T_DIR && ft_strcmp(".", file->d_name) && ft_strcmp("..", file->d_name))
			{
				if (tmp_path)
					free(tmp_path);
				tmp_path = ft_strjoin(all->args->name, "/");
				create_args(all, ft_strjoin(tmp_path, file->d_name), 0);
			}
		}
	}
	closedir(dir);
}
