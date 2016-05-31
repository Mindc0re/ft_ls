/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 09:51:36 by sgaudin           #+#    #+#             */
/*   Updated: 2016/05/31 09:13:32 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		free_list(t_all *all)
{
	FT_INIT(t_dir *, tmp_lst, init_list());
	FT_INIT(t_files *, tmp_files, init_files());
	if (all->args)
	{
		backlist(all, A_DIR);
		while (all->args)
		{
			if (all->args->files)
			{
				while (all->args->files)
				{
					tmp_files = all->args->files->next;
					free(all->args->files);
					all->args->files = tmp_files;
				}
			}
			tmp_lst = all->args->next;
			free(all->args);
			all->args = tmp_lst;
		}
		free(tmp_lst);
		free(tmp_files);
	}
}
