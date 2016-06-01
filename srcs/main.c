/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 10:39:46 by sgaudin           #+#    #+#             */
/*   Updated: 2016/06/01 09:44:13 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	tmp_print_list(t_all *all)
{
	backlist(all, W_FILE);
	while (all->list)
	{
		ft_printf("%s %d\n", all->list->name, all->list->type);
		all->list = all->list->next;
	}
}


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
	all->list = init_file();
}

int			main(int ac, char **av)
{
	t_all *all;

	all = (t_all *)malloc(sizeof(t_all));
	all->ac = ac;
	init_all(all);
	parser_args(av, all);
	tmp_print_list(all);
	free_args(all);
	free_list(all);
	free(all);
	exit(EXIT_SUCCESS);
}
