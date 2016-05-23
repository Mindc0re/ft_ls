/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 11:09:05 by sgaudin           #+#    #+#             */
/*   Updated: 2016/05/23 13:45:43 by sgaudin          ###   ########.fr       */
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
#  define FT_MULTI3(a, b, c)			a = b = c
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
	struct s_files	*next;
	struct s_files	*prev;
}					t_files;

typedef struct		s_dir
{
	char			*name;
	t_files			*files;
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
	t_dir			*dir;
}					t_all;

enum {
	A_DIR,
	A_FILE
}					which;

void				parser_ls(char **av, t_all *all);

void				get_max_length(t_all *all);

t_dir				*init_list(void);
void				backlist(t_all *all, int which);
void				create_node_lst(t_all *all, char *str);

t_files				*init_files(void);

void				free_list(t_all *all);

void				flag_f(t_all *all);

#endif
