/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 17:20:52 by sgaudin           #+#    #+#             */
/*   Updated: 2016/06/10 14:26:31 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char		*set_printf(int length, char *opt)
{
	FT_INIT(char *, tmp, ft_itoa(length));
	FT_INIT(char *, del, tmp);
	tmp = ft_strjoin("%", tmp);
	ft_strdel(&del);
	del = tmp;
	tmp = ft_strjoin(tmp, opt);
	ft_strdel(&del);
	return (tmp);
}

void		print_l(t_all *all, t_files **list)
{
	FT_INIT(char *, tmp, NULL);
	ft_printf("%s ", (*list)->rights);
	ft_printf(tmp = set_printf(all->max_length[0] + 1, "d "), (*list)->links);
	ft_strdel(&tmp);
	ft_printf(tmp = set_printf(-all->max_length[1], "s "), (*list)->own_name);
	ft_strdel(&tmp);
	ft_printf(tmp = set_printf(-all->max_length[2], "s "), (*list)->own_grp);
	ft_strdel(&tmp);
	ft_printf(tmp = set_printf(all->max_length[3] + 1, "d "), (*list)->size);
	ft_strdel(&tmp);
	ft_printf(tmp = set_printf(all->max_length[4], "s "), (*list)->time[0]);
	ft_strdel(&tmp);
	ft_printf(tmp = set_printf(all->max_length[5], "s "), (*list)->time[1]);
	ft_strdel(&tmp);
	ft_printf(tmp = set_printf(all->max_length[6], "s "), (*list)->time[2]);
	ft_strdel(&tmp);
	ft_printf("%s\n", (*list)->name);
//	ft_printf(tmp = set_printf(all->max_length[7], "s\n"), (*list)->name);
}

void		print_list_bis(t_all *all)
{
	if (all->list_bis)
	{
		backlist(&all->list_bis);
		while (all->list_bis->next)
		{
			if (all->flag_l)
				print_l(all, &all->list_bis);
//				ft_printf("%s %D %s %s %jd %s %s %s %s\n", all->list_bis->rights,
//		all->list_bis->links, all->list_bis->own_name, all->list_bis->own_grp,
//		all->list_bis->size, all->list_bis->time[0], all->list_bis->time[1],
//		all->list_bis->time[2], all->list_bis->name);
			else
				ft_printf("%s\n", all->list_bis->name);
			all->list_bis = all->list_bis->next;
		}
		if (all->flag_l)
			print_l(all, &all->list_bis);
//				ft_printf("%s %D %s %s %jd %s %s %s %s\n", all->list_bis->rights,
//		all->list_bis->links, all->list_bis->own_name, all->list_bis->own_grp,
//		all->list_bis->size, all->list_bis->time[0], all->list_bis->time[1],
//		all->list_bis->time[2], all->list_bis->name);
		else
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
				print_l(all, &all->list);
/*				ft_printf("%s %D %s %s %jd %s %s %s %s\n", all->list->rights,
		all->list->links, all->list->own_name, all->list->own_grp,
		all->list->size, all->list->time[0], all->list->time[1],
		all->list->time[2], all->list->name); */
			else
				ft_printf("%s\n", all->list->name);
		}
	}
	else
	{
		if (all->flag_l)
			print_l(all, &all->list);
/*			ft_printf("%s %D %s %s %jd %s %s %s %s\n", all->list->rights,
		all->list->links, all->list->own_name, all->list->own_grp,
		all->list->size, all->list->time[0], all->list->time[1],
		all->list->time[2], all->list->name); */
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
