/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 17:22:32 by cylemair          #+#    #+#             */
/*   Updated: 2019/10/11 17:42:15 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_opt		read_arg(t_opt arg, char c)
{
	if (c == 'l')
		arg._l = 1;
	else if (c == 'R')
		arg._R = 1;
	else if (c == 'a')
		arg._a = 1;
	else if (c == 'r')
		arg._r = 1;
	else if (c == 't')
		arg._t = 1;
	return (arg);
}

t_ls		set_arg(t_ls new, char **av)
{
	int		y;
	int		x;
	int		is_opt;
	int		is_path;

	y = 0;
	is_path = 0;
	while (av[++y])
	{
		x = -1;
		is_opt = 0;
		is_path = create_or_add(&new.array, av[y]);
		while (av[y][++x] && !is_path)
		{
			is_opt = (av[y][x] == '-') ? 1 : is_opt;
			new.arg = (is_opt) ? read_arg(new.arg, av[y][x]) : new.arg;
		}
		if (is_opt && !(BAD_OPTION(new)))
		{
			PR("invalid option", av[y]);
		}
	}
	return (new);
}

t_ls		init_arg(void)
{
	t_ls	new;

	new.arg._l = 0;
	new.arg._R = 0;
	new.arg._a = 0;
	new.arg._r = 0;
	new.arg._t = 0;
	new.file = NULL;
	new._err = NULL;
	new.array = NULL;
	return (new);
}
