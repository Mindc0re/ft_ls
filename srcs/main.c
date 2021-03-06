/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 10:39:46 by sgaudin           #+#    #+#             */
/*   Updated: 2016/06/10 16:34:33 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	init_all(t_all *all)
{
	FT_INIT(int, i, 0);
	all->flag_r_big = 0;
	all->flag_r = 0;
	all->flag_a = 0;
	all->flag_t = 0;
	all->flag_l = 0;
	all->flag_f = 0;
	all->args = init_file();
	all->list = NULL;
	all->list_bis = NULL;
	while (i < 8)
	{
		all->max_length[i] = 0;
		i++;
	}
}

int			main(int ac, char **av)
{
	t_all *all;

	all = (t_all *)malloc(sizeof(t_all));
	all->ac = ac;
	init_all(all);
	parser_args(av, all);
	free_list(&all->args);
	free_list(&all->list);
	free_list(&all->list_bis);
	free(all);
	exit(EXIT_SUCCESS);
}
