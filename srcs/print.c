/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 17:20:52 by sgaudin           #+#    #+#             */
/*   Updated: 2016/06/10 10:54:53 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		print_list_bis(t_all *all)
{
	if (all->list_bis)
	{
		backlist(&all->list_bis);
		while (all->list_bis->next)
		{
			if (all->flag_l)
				ft_printf("%s  %D %s  %s %jd %s %s\n", all->list_bis->rights,
		all->list_bis->links, all->list_bis->own_name, all->list_bis->own_grp,
		all->list_bis->size, all->list_bis->lastmodtime, all->list_bis->name);
			else
				ft_printf("%s\n", all->list_bis->name);
			all->list_bis = all->list_bis->next;
		}
		ft_printf("%s\n", all->list_bis->name);
		free_list(&all->list_bis);
	}
}

void		verif_flag(t_all *all)
{
	if (all->list->name[0] == '.')
	{
		if (all->flag_a)
		{
			if (all->flag_l)
				ft_printf("%s  %D %s  %s %jd %s %s\n", all->list->rights,
		all->list->links, all->list->own_name, all->list->own_grp,
		all->list->size, all->list->lastmodtime, all->list->name);
			else
				ft_printf("%s\n", all->list->name);
		}
	}
	else
	{
		if (all->flag_l)
			ft_printf("%s  %D %s  %s %jd %s %s\n", all->list->rights,
		all->list->links, all->list->own_name, all->list->own_grp,
		all->list->size, all->list->lastmodtime, all->list->name);
		else
			ft_printf("%s\n", all->list->name);
	}
}

void		print_list_reg(t_all *all)
{
	if (all->list)
	{
		backlist(&all->list);
		if (ft_strcmp("./", all->args->name) && all->ac >= 2)
		{
			if (!all->args->prev)
				ft_printf("%s:\n", all->args->name);
			else
				ft_printf("\n%s:\n", all->args->name);
		}
		if (all->flag_l)
			ft_printf("total %d\n", all->total);
		while (all->list->next)
		{
			verif_flag(all);
			if (all->list->next)
				all->list = all->list->next;
			else
				break ;
		}
		verif_flag(all);
	}
}
