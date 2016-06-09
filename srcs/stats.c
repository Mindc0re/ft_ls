/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 13:44:23 by sgaudin           #+#    #+#             */
/*   Updated: 2016/06/09 11:33:39 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		get_time(t_files **new, struct stat *file)
{
	(*new)->lastmodtime = ctime(&file->st_mtime);
	ft_printf("TIME : %s%s\n", (*new)->lastmodtime, (*new)->name);
	//	ft_printf("TEST : %s %D %s %s %jd %s\n", (*new)->rights, (*new)->links, (*new)->own_name, (*new)->own_grp, (*new)->size, (*new)->name);
}

void		get_infos(t_files **new, struct stat *file)
{
	struct passwd	*pwd;
	struct group	*grp;

	pwd = getpwuid(file->st_uid);
	grp = getgrgid(file->st_gid);
	(*new)->links = (unsigned int)file->st_nlink;
	(*new)->own_name = ft_strnew(ft_strlen(pwd->pw_name));
	ft_strcpy((*new)->own_name, pwd->pw_name);
	(*new)->own_grp = ft_strnew(ft_strlen(grp->gr_name));
	ft_strcpy((*new)->own_grp, grp->gr_name);
	(*new)->size = (intmax_t)file->st_size;
	get_time(new, file);
}

void		get_rights(t_files **new, struct stat *file)
{
	(*new)->rights[0] = '-';
	(*new)->rights[0] = (S_ISREG(file->st_mode)) ? '-' : (*new)->rights[0];
	(*new)->rights[0] = (S_ISDIR(file->st_mode)) ? 'd' : (*new)->rights[0];
	(*new)->rights[0] = (S_ISCHR(file->st_mode)) ? 'c' : (*new)->rights[0];
	(*new)->rights[0] = (S_ISBLK(file->st_mode)) ? 'b' : (*new)->rights[0];
	(*new)->rights[0] = (S_ISFIFO(file->st_mode)) ? 'p' : (*new)->rights[0];
	(*new)->rights[0] = (S_ISLNK(file->st_mode)) ? 'l' : (*new)->rights[0];
	(*new)->rights[0] = (S_ISSOCK(file->st_mode)) ? 's' : (*new)->rights[0];
	(*new)->rights[1] = file->st_mode & S_IRUSR ? 'r' : '-';
	(*new)->rights[2] = file->st_mode & S_IWUSR ? 'w' : '-';
	(*new)->rights[3] = file->st_mode & S_IXUSR ? 'x' : '-';
	(*new)->rights[4] = file->st_mode & S_IRGRP ? 'r' : '-';
	(*new)->rights[5] = file->st_mode & S_IWGRP ? 'w' : '-';
	(*new)->rights[6] = file->st_mode & S_IXGRP ? 'x' : '-';
	(*new)->rights[7] = file->st_mode & S_IROTH ? 'r' : '-';
	(*new)->rights[8] = file->st_mode & S_IWOTH ? 'w' : '-';
	(*new)->rights[9] = file->st_mode & S_IXOTH ? 'x' : '-';
	(*new)->rights[10] = '\0';
	get_infos(new, file);
}

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
		(*new)->type = T_REG;
	get_rights(new, file);
}
