/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 12:39:34 by sgaudin           #+#    #+#             */
/*   Updated: 2016/06/10 17:25:27 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		get_total_blocks(t_all *all)
{
	int	blocks;

	blocks = 0;
	if (all->flag_l)
	{
		backlist(&all->list);
		while (all->list)
		{
			blocks += all->list->nb_blocks;
			if (all->list->next)
				all->list = all->list->next;
			else
				break ;
		}
		all->total = blocks;
	}
}

void		create_link(t_files **new, struct stat *file, t_all *all)
{
	if ((*new)->rights[0] == 'l' && all->flag_l)
	{
		(*new)->tmp_lnk = (char *)malloc(sizeof(char) * file->st_size + 1);
		FT_INIT(char *, del, NULL);
		del = (*new)->name;
		(*new)->name = ft_strjoin((*new)->name, " -> ");
		free(del);
		readlink((*new)->path, (*new)->tmp_lnk, file->st_size + 1);
	}
}

void		create_path(t_files **list, char *str, t_all *all)
{
	FT_INIT(char *, del, NULL);
	(*list)->path = ft_strjoin(all->args->name, "/");
	del = (*list)->path;
	(*list)->path = ft_strjoin((*list)->path, str);
	free(del);
}
