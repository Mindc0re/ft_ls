/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 13:32:01 by sgaudin           #+#    #+#             */
/*   Updated: 2016/06/06 13:59:32 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		tri_lst(t_list **list)
{
	t_list *tmp;

	backlist(all, W_LIST, (*list));
}

void		tri_args(t_dir **args)
{
	t_dir *tmp;

	backlist(all, W_ARGS, NULL);
	while ((*args))
	{
		
	}
}
