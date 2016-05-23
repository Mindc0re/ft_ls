/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 11:57:39 by sgaudin           #+#    #+#             */
/*   Updated: 2016/05/23 12:46:24 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

void		flag_f(t_all *all)
{
	DIR				*dir;
	struct dirent	*file;
	int				i;

	if (!(dir = opendir(all->dir->name)))
	{
		perror("ft_ls");
		exit(EXIT_FAILURE);
	}
	while ((file = readdir(dir)) != NULL)
	{
		i = 0;
		ft_printf("%s", file->d_name);
		while (i + (int)ft_strlen(file->d_name) < all->max_length)
		{
			ft_putchar(' ');
			i++;
		}
	}
	ft_putchar('\n');
	closedir(dir);
}
