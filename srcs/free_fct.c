/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 09:51:36 by sgaudin           #+#    #+#             */
/*   Updated: 2016/06/03 14:34:06 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		free_args(t_all *all)
{
	if (all->args)
	{
		FT_INIT(t_dir *, tmp_lst, init_list());
		backlist(all, W_ARGS, NULL);
		while (all->args)
		{
			tmp_lst = all->args->next;
//			free(all->args->name);
			free(all->args);
			all->args = tmp_lst;
		}
		free(tmp_lst);
	}
}

void		free_list(t_all *all, t_files **list)
{
	if ((*list))
	{
//		ft_printf("In the free fct\n");
		FT_INIT(t_files *, tmp_lst, init_file());
		backlist(all, W_FILE, &(*list));
		while ((*list))
		{
			tmp_lst = (*list)->next;
			free((*list));
			(*list) = tmp_lst;
		}
		free(tmp_lst);
	}
}
