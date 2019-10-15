/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:07:44 by cylemair          #+#    #+#             */
/*   Updated: 2019/10/15 12:32:03 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		more_print_l(t_reader *current)
{
	ft_putchar(' ');
	ft_putnbr(current->sb.st_nlink);
	ft_putchar(' ');
	ft_putstr((getpwuid(current->sb.st_uid))->pw_name);
	ft_putchar(' ');
	ft_putstr((getgrgid(current->sb.st_gid))->gr_name);
	ft_putchar(' ');
	ft_putnbr(current->sb.st_size);
	ft_putchar('\t');
	print_time(current);
	ft_putchar('\t');
}

void		print_l(t_ls meta, t_reader *current)
{
	char	linkname[_PC_PATH_MAX];
	ssize_t r;

	if (!meta.arg.a && (!ft_strcmp(current->name, ".")
		|| !ft_strcmp(current->name, "..")))
		return ;
	print_right(current->sb.st_mode);
	more_print_l(current);
	CYAN(current->name);
	if (S_ISLNK(current->sb.st_mode))
	{
		r = readlink(current->path, linkname, _PC_PATH_MAX);
		if (r != -1)
			linkname[r] = '\0';
		ft_putstr(" -> ");
		ft_putstr(linkname);
	}
	ft_putstr("\n\033[0m");
}
