/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 09:26:44 by sgaudin           #+#    #+#             */
/*   Updated: 2016/05/23 13:35:31 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		backlist(t_all *all, int which)
{
	if (which == A_DIR)
	{
		if (all->dir)
		{
			while (all->dir->prev)
				all->dir = all->dir->prev;
		}
	}
	else if (which == A_FILE)
	{
		if (all->dir->files)
		{
			while (all->dir->files->prev)
				all->dir->files = all->dir->files->prev;
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

void		create_node_lst(t_all *all, char *str)
{
	static int	check = 0;
	t_dir		*new;

	if (!check++)
		all->dir->name = str;
	else
	{
		new = init_list();
		new->name = str;
		new->prev = all->dir;
		all->dir->next = new;
		all->dir = all->dir->next;
	}
}

void		create_node_file(t_all *all, char *str)
{
	static int	check = 0;
	t_files		*new;

	if (!check++)
		all->dir->files->name = str;
	else
	{
		new = init_files();
		new->name = str;
		new->prev = all->dir->files;
		all->dir->files->next = new;
		all->dir->files = all->dir->files->next;
	}
}
