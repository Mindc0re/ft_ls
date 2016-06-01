/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 09:51:36 by sgaudin           #+#    #+#             */
/*   Updated: 2016/05/31 15:19:52 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		free_args(t_all *all)
{
	FT_INIT(t_dir *, tmp_lst, init_list());
	if (all->args)
	{
		backlist(all, W_ARGS);
		while (all->args)
		{
			tmp_lst = all->args->next;
			free(all->args);
			all->args = tmp_lst;
		}
	}
	free(tmp_lst);
}

void		free_list(t_all *all)
{
	FT_INIT(t_files *, tmp_lst, init_file());
	if (all->list)
	{
		backlist(all, W_FILE);
		while (all->list)
		{
			tmp_lst = all->list->next;
			free(all->list);
			all->list = tmp_lst;
		}
	}
	free(tmp_lst);
}
