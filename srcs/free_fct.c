/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 09:51:36 by sgaudin           #+#    #+#             */
/*   Updated: 2016/06/10 13:24:48 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		free_args(t_all *all)
{
	if (all->args)
	{
		FT_INIT(t_files *, tmp_lst, init_file());
		backlist(&all->args);
		while (all->args)
		{
			tmp_lst = all->args->next;
			free(all->args);
			all->args = tmp_lst;
		}
		free(tmp_lst);
	}
}

void		free_list(t_files **list)
{
	if ((*list))
	{
		FT_INIT(t_files *, tmp_lst, init_file());
		backlist(&(*list));
		while ((*list))
		{
			tmp_lst = (*list)->next;
			if ((*list)->path)
				free((*list)->path);
			if ((*list)->time[0])
			{
				free((*list)->time[0]);
				free((*list)->time[1]);
				free((*list)->time[2]);
			}
			if ((*list)->own_grp)
				free((*list)->own_grp);
			if ((*list)->own_name)
				free((*list)->own_name);
			free((*list));
			(*list) = tmp_lst;
		}
		free(tmp_lst);
	}
}
