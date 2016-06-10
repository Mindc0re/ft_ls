/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 12:39:34 by sgaudin           #+#    #+#             */
/*   Updated: 2016/06/10 10:53:11 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void			get_max_length(t_all *all)
{
	DIR				*dir;
	struct dirent	*file;

	if (!(dir = opendir(all->args->name)))
	{
		perror("ft_ls");
		exit(EXIT_FAILURE);
	}
	while ((file = readdir(dir)) != NULL)
	{
		if ((int)ft_strlen(file->d_name) + 1 > all->max_length)
			all->max_length = (int)ft_strlen(file->d_name) + 1;
	}
	if (dir)
		closedir(dir);
}

void			get_total_blocks(t_all *all)
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
