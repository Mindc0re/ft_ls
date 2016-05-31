/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_opendir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 10:58:04 by sgaudin           #+#    #+#             */
/*   Updated: 2016/05/24 11:10:38 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		test_opendir(char *str)
{
	DIR				*dir;
	struct stat		file;

	if (!(dir = opendir(str)))
	{
		stat(str, &file);
		if (S_ISREG(file.st_mode))
			printf("YAS\n");
		else
			perror("tamer");
	}
	else
		closedir(dir);
}

int			main(int ac, char **av)
{
	if (ac == 2)
		test_opendir(av[1]);
	return (0);
}
