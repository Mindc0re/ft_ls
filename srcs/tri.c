/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 13:32:01 by sgaudin           #+#    #+#             */
/*   Updated: 2016/06/08 09:11:17 by sgaudin          ###   ########.fr       */
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

void		tri_lst(t_files **list)
{
	FT_INIT(int, check, 0);
	backlist(NULL, W_FILE, &(*list));
	while ((*list))
	{
		if ((*list)->next)
		{
			if (ft_strcmp((*list)->name, (*list)->next->name) > 0)
			{
				swap(&(*list));
				check++;
			}
			if ((*list)->next)
				(*list) = (*list)->next;
		}
		else
			break ;
	}
	if (check)
		tri_lst(list);
}
