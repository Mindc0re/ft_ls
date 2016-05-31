/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 10:39:46 by sgaudin           #+#    #+#             */
/*   Updated: 2016/05/31 09:23:30 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
/*
static void	tmp_print_list(t_all *all)
{
	t_dir *tmp;

	tmp = all->args;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		ft_printf("%s\n", tmp->name);
		tmp = tmp->next;
	}
	free(tmp);
}
*/

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
	all->args->files = init_files();
}

int			main(int ac, char **av)
{
	t_all *all;

	all = (t_all *)malloc(sizeof(t_all));
	all->ac = ac;
	init_all(all);
	parser_args(av, all);
//	tmp_print_list(all);
	backlist(all, A_DIR);
	free_list(all);
	free(all);
	exit(EXIT_SUCCESS);
}
