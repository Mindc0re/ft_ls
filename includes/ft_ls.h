/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 11:09:05 by sgaudin           #+#    #+#             */
/*   Updated: 2016/05/18 11:15:55 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/stat.h>
//# include <uuid/uuid.h>
# include <sys/xattr.h>
# include <time.h>
# include <stdlib.h>
# include <stdio.h>

# include "../libft/includes/libft.h"

# define FT_INIT(t, n, v)			t n = v
# define FT_TER(si, alors, sinon)	si ? alors : sinon
# define FT_MULTI3(a, b, c)			a = b = c

typedef struct	s_all
{
	int			ac;
	int			flag_R;
	int			flag_r;
	int			flag_t;
	int			flag_a;
	int			flag_l;
}				t_all;

void			parser(char **av, t_all *all);

#endif
