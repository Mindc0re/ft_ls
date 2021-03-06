/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 13:32:01 by sgaudin           #+#    #+#             */
/*   Updated: 2016/06/10 11:46:59 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		swap(t_files **list)
{
	t_files tmp;

	tmp = *(*list)->next;
	(*list)->next->prev = (*list)->prev;
	if ((*list)->next->next)
		(*list)->next->next->prev = (*list);
	if ((*list)->prev)
		(*list)->prev->next = (*list)->next;
	(*list)->next->next = (*list);
	(*list)->prev = (*list)->next;
	(*list)->next = tmp.next;
}

int			tri_flag(t_files **l, t_all *a)
{
	if (ft_strcmp((*l)->name, (*l)->next->name) < 0 && a->flag_r && !a->flag_t)
	{
		swap(&(*l));
		return (1);
	}
	if (((*l)->time_sec - (*l)->next->time_sec) < 0 && a->flag_t && !a->flag_r)
	{
		swap(&(*l));
		return (1);
	}
	if (a->flag_t && a->flag_r && ((*l)->time_sec - (*l)->next->time_sec) > 0)
	{
		swap(&(*l));
		return (1);
	}
	return (0);
}

void		tri_lst(t_files **list, t_all *all)
{
	FT_INIT(int, check, 0);
	backlist(&(*list));
	while ((*list))
	{
		if ((*list)->next)
		{
			if (all->flag_r || all->flag_t)
				check = tri_flag(&(*list), all) == 1 ? check + 1 : check;
			else
			{
				if (ft_strcmp((*list)->name, (*list)->next->name) > 0)
				{
					swap(&(*list));
					check++;
				}
			}
			if ((*list)->next)
				(*list) = (*list)->next;
		}
		else
			break ;
	}
	if (check)
		tri_lst(list, all);
}
