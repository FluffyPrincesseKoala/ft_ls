/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:07:44 by cylemair          #+#    #+#             */
/*   Updated: 2019/10/19 19:43:13 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void				more_print_l(t_reader *current)
{
	struct passwd	*uid;
	struct group	*gid;

	ft_putchar(' ');
	ft_putnbr(current->sb.st_nlink);
	ft_putchar(' ');
	if ((uid = getpwuid(current->sb.st_uid)))
		ft_putstr(uid->pw_name);
	ft_putchar('\t');
	if ((gid = getgrgid(current->sb.st_gid)))
		ft_putstr(gid->gr_name);
	ft_putchar('\t');
	if (S_ISCHR(current->sb.st_mode) || S_ISBLK(current->sb.st_mode))
	{
		ft_putnbr(major(current->sb.st_rdev));
		ft_putstr(",\t");
		ft_putnbr(minor(current->sb.st_rdev));
	}
	else
		ft_putnbr(current->sb.st_size);
	ft_putchar('\t');
	print_time(current);
	ft_putchar('\t');
}

void		color_name(t_reader *current)
{
	if (S_ISLNK(current->sb.st_mode))
	{
		PURPLE(current->name);
	}
	else if (S_ISDIR(current->sb.st_mode))
	{
		CYAN(current->name);
	}
	else if (S_ISCHR(current->sb.st_mode))
	{
		YELLOW(current->name);
	}
	else if (S_ISBLK(current->sb.st_mode) || S_ISSOCK(current->sb.st_mode))
	{
		BLUE(current->name);
	}
	else if (S_ISFIFO(current->sb.st_mode))
	{
		YELLOW_2(current->name);
	}
	else
		ft_putstr(current->name);
	ft_putstr("\033[0m");
}

void		print_l(t_ls meta, t_reader *current)
{
	char	linkname[PATH_MAX];
	ssize_t r;

	if (!meta.arg.a && (!ft_strcmp(current->name, ".")
		|| !ft_strcmp(current->name, "..")))
		return ;
	print_right(current->sb.st_mode);
	more_print_l(current);
	color_name(current);
	if (S_ISLNK(current->sb.st_mode))
	{
		r = readlink(current->path, linkname, PATH_MAX - 1);
		if (r != -1)
		{
			linkname[r] = '\0';
			ft_putstr(" -> ");
			ft_putstr(linkname);
		}
	}
	ft_putstr("\n\033[0m");
}
