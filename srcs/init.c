/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 17:22:32 by cylemair          #+#    #+#             */
/*   Updated: 2019/10/15 17:09:32 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_opt		read_arg(t_opt arg, char c)
{
	if (c == 'l')
		arg.l = 1;
	else if (c == 'R')
		arg.br = 1;
	else if (c == 'a')
		arg.a = 1;
	else if (c == 'r')
		arg.r = 1;
	else if (c == 't')
		arg.t = 1;
	return (arg);
}

void		error_arg(char *name)
{
	ft_putstr("\033[1;31m");
	ft_putstr_fd("ls: ", 2);
	ft_putstr_fd("invalid option", 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("\n", 2);
	RESET();
	exit(-1);
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
		if (is_opt && !(OPTION(new)))
		{
			error_arg(av[y]);
		}
	}
	return (new);
}

t_ls		init_arg(void)
{
	t_ls	new;

	new.arg.l = 0;
	new.arg.br = 0;
	new.arg.a = 0;
	new.arg.r = 0;
	new.arg.t = 0;
	new.file = NULL;
	new.err = NULL;
	new.array = NULL;
	return (new);
}
