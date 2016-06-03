/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 10:39:46 by sgaudin           #+#    #+#             */
/*   Updated: 2016/06/03 14:34:59 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	init_all(t_all *all)
{
	all->flag_r_big = 0;
	all->flag_r = 0;
	all->flag_a = 0;
	all->flag_t = 0;
	all->flag_l = 0;
	all->flag_f = 0;
	all->max_length = 0;
	all->args = init_list();
	all->list = NULL;
	all->list_bis = NULL;
}

int			main(int ac, char **av)
{
	t_all *all;

	all = (t_all *)malloc(sizeof(t_all));
	all->ac = ac;
	init_all(all);
	parser_args(av, all);
	free_args(all);
	free_list(all, &all->list);
	free_list(all, &all->list_bis);
	free(all);
	exit(EXIT_SUCCESS);
}
