/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 09:26:44 by sgaudin           #+#    #+#             */
/*   Updated: 2016/06/10 11:45:01 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		backlist(t_files **list)
{
	if ((*list))
	{
		while ((*list)->prev)
			(*list) = (*list)->prev;
	}
}

static void	first_arg(t_all *all, char *str, struct stat *file)
{
	all->args->name = ft_strdup(str);
	get_type(&all->args, &file);
}

t_files		*init_file(void)
{
	t_files	*files;

	files = (t_files *)malloc(sizeof(t_files));
	files->type = -1;
	files->links = 0;
	files->own_name = NULL;
	files->own_grp = NULL;
	files->size = -1;
	files->lastmodtime = NULL;
	files->name = NULL;
	files->prev = NULL;
	files->next = NULL;
	return (files);
}

void		create_args(t_all *all, char *str, int next)
{
	struct stat	file;
	static int	check = 0;
	t_files		*new;

	lstat(str, &file);
	if (!check++)
		first_arg(all, str, &file);
	else
	{
		new = init_file();
		new->name = ft_strdup(str);
		new->prev = all->args;
		get_type(&new, &file);
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
		lstat((*list)->path, &file);
		get_type(&(*list), &file);
	}
	else
	{
		new = init_file();
		new->name = ft_strdup(str);
		new->path = ft_strjoin(all->args->name, "/");
		new->path = ft_strjoin(new->path, str);
		lstat(new->path, &file);
		get_type(&new, &file);
		new->prev = (*list);
		(*list)->next = new;
		(*list) = (*list)->next;
	}
}
