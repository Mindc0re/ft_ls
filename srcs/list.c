/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 09:26:44 by sgaudin           #+#    #+#             */
/*   Updated: 2016/06/08 09:00:18 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		backlist(t_all *all, int which, t_files **list)
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
		if ((*list))
		{
			while ((*list)->prev)
				(*list) = (*list)->prev;
		}
	}
}

t_dir		*init_list(void)
{
	t_dir	*dir;

	dir = (t_dir *)malloc(sizeof(t_dir));
	dir->prev = NULL;
	dir->next = NULL;
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

int			create_args(t_all *all, char *str, int next)
{
	static int	check = 0;
	t_dir		*new;

	if (!check++)
	{
		all->args->name = ft_strnew(ft_strlen(str));
		all->args->name = str;
	}
	else
	{
		new = init_list();
		new->name = ft_strnew(ft_strlen(str));
		new->name = str;
		new->prev = all->args;
		if (!next)
		{
			new->next = all->args->next;
			all->args->next = new;
		}
		else
		{
			all->args->next = new;
			all->args = all->args->next;
		}
	}
	return (0);
}

void		create_list(char *str, t_files **list, t_all *all)
{
	t_files			*new;
	struct stat		file;

	if (!(*list))
	{
		(*list) = init_file();
		(*list)->name = str;
		(*list)->path = ft_strjoin(all->args->name, "/");
		(*list)->path = ft_strjoin((*list)->path, str);
		stat((*list)->path, &file);
		get_type(&(*list), &file);
	}
	else
	{
		new = init_file();
		new->name = str;
		new->path = ft_strjoin(all->args->name, "/");
		new->path = ft_strjoin(new->path, str);
		stat(new->path, &file);
		get_type(&new, &file);
		new->prev = (*list);
		(*list)->next = new;
		(*list) = (*list)->next;
	}
}
