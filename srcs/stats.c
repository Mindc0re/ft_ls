/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 13:44:23 by sgaudin           #+#    #+#             */
/*   Updated: 2016/06/10 11:36:59 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		get_time(t_files **new, struct stat *file)
{
	char			*time_str;
	char			**tmp_tab;
	time_t			tm;
	char 			*timestamp;

	tm = time(NULL);
	timestamp = ctime(&tm);
	time_str = ctime(&file->st_mtime);
	tmp_tab = ft_strsplit(time_str, ' ');
	time_str = ft_strsub(tmp_tab[3], 0,
	ft_strlen(tmp_tab[3]) - ft_strlen(ft_strrchr(tmp_tab[3], ':')));
	(*new)->time_sec = file->st_mtimespec.tv_sec;
	(*new)->lastmodtime = ft_strjoin(tmp_tab[1], " ");
	(*new)->lastmodtime = ft_strjoin((*new)->lastmodtime, tmp_tab[2]);
	(*new)->lastmodtime = ft_strjoin((*new)->lastmodtime, " ");
	(*new)->lastmodtime = ft_strjoin((*new)->lastmodtime, time_str);
}

void		get_infos(t_files **new, struct stat *file)
{
	struct passwd	*pwd;
	struct group	*grp;

	pwd = getpwuid(file->st_uid);
	grp = getgrgid(file->st_gid);
	(*new)->links = (unsigned int)file->st_nlink;
	(*new)->own_name = pwd ? ft_strnew(ft_strlen(pwd->pw_name)) : NULL;
	(*new)->own_grp = grp ? ft_strnew(ft_strlen(grp->gr_name)) : NULL;
	if ((*new)->own_name)
		ft_strcpy((*new)->own_name, pwd->pw_name);
	if ((*new)->own_grp)
		ft_strcpy((*new)->own_grp, grp->gr_name);
	(*new)->size = (intmax_t)file->st_size;
	(*new)->nb_blocks = file->st_blocks;
	get_time(new, file);
	if ((*new)->rights[0] == 'l')
	{
		FT_INIT(char *, linkname, (char *)malloc(sizeof(char) * file->st_size + 1));
		readlink((*new)->path, linkname, file->st_size + 1);
		linkname = ft_strjoin(" -> ", linkname);
		(*new)->name = ft_strjoin((*new)->name, linkname);
	}
}

void		get_rights(t_files **new, struct stat *file)
{
	(*new)->rights[0] = '-';
	(*new)->rights[0] = (S_ISREG(file->st_mode)) ? '-' : (*new)->rights[0];
	(*new)->rights[0] = (S_ISDIR(file->st_mode)) ? 'd' : (*new)->rights[0];
	(*new)->rights[0] = (S_ISCHR(file->st_mode)) ? 'c' : (*new)->rights[0];
	(*new)->rights[0] = (S_ISBLK(file->st_mode)) ? 'b' : (*new)->rights[0];
	(*new)->rights[0] = (S_ISFIFO(file->st_mode)) ? 'p' : (*new)->rights[0];
	(*new)->rights[0] = (S_ISSOCK(file->st_mode)) ? 's' : (*new)->rights[0];
	(*new)->rights[0] = (S_ISLNK(file->st_mode)) ? 'l' : (*new)->rights[0];
	(*new)->rights[1] = file->st_mode & S_IRUSR ? 'r' : '-';
	(*new)->rights[2] = file->st_mode & S_IWUSR ? 'w' : '-';
	(*new)->rights[3] = file->st_mode & S_IXUSR ? 'x' : '-';
	(*new)->rights[4] = file->st_mode & S_IRGRP ? 'r' : '-';
	(*new)->rights[5] = file->st_mode & S_IWGRP ? 'w' : '-';
	(*new)->rights[6] = file->st_mode & S_IXGRP ? 'x' : '-';
	(*new)->rights[7] = file->st_mode & S_IROTH ? 'r' : '-';
	(*new)->rights[8] = file->st_mode & S_IWOTH ? 'w' : '-';
	(*new)->rights[9] = file->st_mode & S_IXOTH ?
	FT_TER(file->st_mode & S_ISVTX, 't', 'x') :
	FT_TER(file->st_mode & S_ISVTX, 'T', '-');
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
