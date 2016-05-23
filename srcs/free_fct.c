/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 09:51:36 by sgaudin           #+#    #+#             */
/*   Updated: 2016/05/23 10:51:26 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		free_list(t_all *all)
{
	FT_INIT(t_dir *, tmp_lst, init_list());
	FT_INIT(t_files *, tmp_files, init_files());
	if (all->dir)
	{
		while (all->dir)
		{
			if (all->dir->files)
			{
				while (all->dir->files)
				{
					tmp_files = all->dir->files->next;
					free(all->dir->files);
					all->dir->files = tmp_files;
				}
			}
			tmp_lst = all->dir->next;
			free(all->dir);
			all->dir = tmp_lst;
		}
		free(tmp_lst);
		free(tmp_files);
	}
}
