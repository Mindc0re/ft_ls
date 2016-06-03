/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 13:44:23 by sgaudin           #+#    #+#             */
/*   Updated: 2016/06/03 16:07:20 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		get_type(t_files **new, struct stat *file)
{
	if (S_ISREG(file->st_mode))
		(*new)->type = T_REG;
	else if (S_ISDIR(file->st_mode))
		(*new)->type = T_DIR;
	else if (S_ISCHR(file->st_mode))
		(*new)->type = T_CHR;
	else if (S_ISBLK(file->st_mode))
		(*new)->type = T_BLK;
	else if (S_ISFIFO(file->st_mode))
		(*new)->type = T_FIFO;
	else if (S_ISLNK(file->st_mode))
		(*new)->type = T_LINK;
	else if (S_ISSOCK(file->st_mode))
		(*new)->type = T_SOCK;
	else
		(*new)->type = -1;
//	ft_printf("file name : %s, (*new) name : %s, (*new) type : %d\n", (*new)->name, (*new)->name, (*new)->type);
}
