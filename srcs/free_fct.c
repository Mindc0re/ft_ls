/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 09:51:36 by sgaudin           #+#    #+#             */
/*   Updated: 2016/06/10 17:25:12 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		free_tab(char **tab)
{
	int i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

void		free_node(t_files **list)
{
	if ((*list))
	{
		if ((*list)->path != NULL)
			free((*list)->path);
		if ((*list)->time[0] != NULL && (*list)->time[1] != NULL
			&& (*list)->time[2] != NULL)
		{
			free((*list)->time[0]);
			free((*list)->time[1]);
			free((*list)->time[2]);
		}
		if ((*list)->own_grp != NULL)
			free((*list)->own_grp);
		if ((*list)->own_name != NULL)
			free((*list)->own_name);
		if ((*list)->name != NULL)
			free((*list)->name);
		free((*list));
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
			free_node(list);
			(*list) = tmp_lst;
		}
		free(tmp_lst);
	}
}
