/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 11:09:05 by sgaudin           #+#    #+#             */
/*   Updated: 2016/06/07 11:14:27 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <time.h>
# include <stdlib.h>
# include <stdio.h>

# include "../libft/includes/libft.h"

# ifndef FT_INIT
#  define FT_INIT(t, n, v)			t n = v
# endif

# ifndef FT_TER
#  define FT_TER(si, alors, sinon)	si ? alors : sinon
# endif

# ifndef FT_MULTI3
#  define FT_MULTI3(a, b, c)		a = b = c
# endif

typedef struct		s_files
{
	int				type;
	char			*rights;
	int				links;
	char			*own_name;
	char			*own_grp;
	int				size;
	int				timestamp;
	char			*name;
	char			*path;
	struct s_files	*next;
	struct s_files	*prev;
}					t_files;

typedef struct		s_dir
{
	char			*name;
	struct s_dir	*prev;
	struct s_dir	*next;
}					t_dir;

typedef struct		s_all
{
	int				ac;
	int				flag_r_big;
	int				flag_r;
	int				flag_t;
	int				flag_a;
	int				flag_l;
	int				flag_f;
	int				max_length;
	t_dir			*args;
	t_files			*list;
	t_files			*list_bis;
}					t_all;

enum {
	W_ARGS,
	W_FILE,
	W_LIST,
	W_LIST_BIS
}					which;

enum {
	T_REG = 1,
	T_DIR,
	T_CHR,
	T_BLK,
	T_FIFO,
	T_LINK,
	T_SOCK
}					types;

void				get_max_length(t_all *all);

t_files				*init_file(void);
t_dir				*init_list(void);
void				backlist(t_all *all, int which, t_files **list);

int					create_args(t_all *all, char *str, int next);
void				create_list(char *str, t_files **list, t_all *all);
void				parser_args(char **av, t_all *all);
void				read_dir(t_all *all, char *str);
void				print_list(t_all *all);
void				tri_lst(t_files **list);

void				get_type(t_files **files, struct stat *file);

void				free_args(t_all *all);
void				free_list(t_all *all, t_files **list);

void				flag_f(t_all *all);

#endif
