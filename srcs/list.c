/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 09:26:44 by sgaudin           #+#    #+#             */
/*   Updated: 2016/06/02 09:58:17 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		backlist(t_all *all, int which)
{
	if (which == W_ARGS)
	{
		if (all->args)
		{
			while (all->args->prev)
				all->args = all->args->prev;
		}
	}
	else if (which == W_FILE)
	{
		if (all->list)
		{
			while (all->list->prev)
				all->list = all->list->prev;
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

t_files		*init_file(void)
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
	t_dir		*new;

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

void		create_list(t_all *all, char *str)
{
	t_files			*new;
	struct stat		file;

	if (!all->list)
	{
		all->list = init_file();
		all->list->name = str;
		stat(str, &file);
		get_type(all->list, file);
	}
	else
	{
		new = init_file();
		stat(str, &file);
		get_type(new, file);
		new->name = str;
		new->prev = all->list;
		all->list->next = new;
		all->list = all->list->next;
	}
}
