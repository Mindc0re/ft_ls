/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 09:26:44 by sgaudin           #+#    #+#             */
/*   Updated: 2016/05/31 09:26:34 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		backlist(t_all *all, int which)
{
	if (which == A_DIR)
	{
		if (all->args)
		{
			while (all->args->prev)
				all->args = all->args->prev;
		}
	}
	else if (which == A_FILE)
	{
		if (all->args->files)
		{
			while (all->args->files->prev)
				all->args->files = all->args->files->prev;
		}
	}
}

t_dir		*init_list(void)
{
	t_dir	*dir;

	dir = (t_dir *)malloc(sizeof(t_dir));
	dir->prev = NULL;
	dir->next = NULL;
	dir->files = NULL;
	dir->name = NULL;
	return (dir);
}

t_files		*init_files(void)
{
	t_files	*files;

	files = (t_files *)malloc(sizeof(t_files));
	files->type = -1;
	files->rights = NULL;
	files->links = -1;
	files->own_name = NULL;
	files->own_grp = NULL;
	files->size = -1;
	files->timestamp = -1;
	files->name = NULL;
	files->prev = NULL;
	files->next = NULL;
	return (files);
}

int			create_args(t_all *all, char *str)
{
	static int	check = 0;
	struct stat	file;
	t_dir		*new;

	stat(str, &file);
	if (!S_ISDIR(file.st_mode))
	{
		create_node_file(all, str);
		return (0);
	}
	if (!check++)
		all->args->name = str;
	else
	{
		new = init_list();
		new->name = str;
		new->prev = all->args;
		all->args->next = new;
		all->args = all->args->next;
	}
	return (0);
}

void		create_node_file(t_all *all, char *str)
{
	static int	check = 0;
	t_files		*new;

	if (!check++)
		all->args->files->name = str;
	else
	{
		new = init_files();
		new->name = str;
		new->prev = all->args->files;
		all->args->files->next = new;
		all->args->files = all->args->files->next;
	}
}
