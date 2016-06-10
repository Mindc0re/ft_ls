/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 13:44:23 by sgaudin           #+#    #+#             */
/*   Updated: 2016/06/10 13:53:08 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		get_max_lengths(t_files **new, t_all *all)
{
	all->max_length[0] = (int)ft_strlen(ft_itoa((*new)->links)) > all->max_length[0]
		? (int)ft_strlen(ft_itoa((*new)->links)) : all->max_length[0];
	all->max_length[1] = (int)ft_strlen((*new)->own_name) > all->max_length[1] ?
		(int)ft_strlen((*new)->own_name) : all->max_length[1];
	all->max_length[2] = (int)ft_strlen((*new)->own_grp) > all->max_length[1] ?
		(int)ft_strlen((*new)->own_grp) : all->max_length[2];
	all->max_length[3] = (int)ft_strlen(ft_itoa((*new)->size)) > all->max_length[3]
		? (int)ft_strlen(ft_itoa((*new)->size)) : all->max_length[3];
	all->max_length[4] = (int)ft_strlen((*new)->time[0]) > all->max_length[4] ?
		(int)ft_strlen((*new)->time[0]) : all->max_length[4];
	all->max_length[5] = (int)ft_strlen((*new)->time[1]) > all->max_length[5] ?
		(int)ft_strlen((*new)->time[1]) : all->max_length[5];
	all->max_length[6] = (int)ft_strlen((*new)->time[2]) > all->max_length[6] ?
		(int)ft_strlen((*new)->time[2]) : all->max_length[6];
	all->max_length[7] = (int)ft_strlen((*new)->name) > all->max_length[7] ?
		(int)ft_strlen((*new)->name) : all->max_length[7];
}

void		get_time(t_files **new, struct stat *file, t_all *all)
{
	char			*time_str;
	char			**tmp_tab;
	long int		timestamp;

	timestamp = file->st_mtimespec.tv_sec - time(NULL);
	timestamp = timestamp < 0 ? -timestamp : timestamp;
	time_str = ft_strdup(ctime(&file->st_mtime));
	tmp_tab = ft_strsplit(time_str, ' ');
	time_str = ft_strsub(tmp_tab[3], 0,
	ft_strlen(tmp_tab[3]) - ft_strlen(ft_strrchr(tmp_tab[3], ':')));
	(*new)->time_sec = file->st_mtimespec.tv_sec;
	(*new)->time[0] = ft_strdup(tmp_tab[1]);
	(*new)->time[1] = ft_strdup(tmp_tab[2]);
	(*new)->time[2] = timestamp > SIX_MONTHS ?
	ft_strsub(tmp_tab[4], 0, ft_strlen(tmp_tab[4]) - 1) : time_str;
	(*new)->time[3] = NULL;
	get_max_lengths(new, all);
}

void		get_infos(t_files **new, struct stat *file, t_all *all)
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
	get_time(new, file, all);
	if ((*new)->rights[0] == 'l')
	{
		FT_INIT(char *, link, (char *)malloc(sizeof(char) * file->st_size + 1));
		readlink((*new)->path, link, file->st_size + 1);
		link = ft_strjoin(" -> ", link);
		(*new)->name = ft_strjoin((*new)->name, link);
	}
}

void		get_rights(t_files **new, struct stat *file, t_all *all)
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
	get_infos(new, file, all);
}

void		get_type(t_files **new, struct stat *file, t_all *all)
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
	get_rights(new, file, all);
}
