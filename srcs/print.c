/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 21:36:12 by princesse         #+#    #+#             */
/*   Updated: 2019/10/19 20:49:35 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char		*print_type(mode_t m)
{
	if (S_ISDIR(m))
		return ("d");
	else if (S_ISCHR(m))
		return ("c");
	else if (S_ISBLK(m))
		return ("b");
	else if (S_ISFIFO(m))
		return ("p");
	else if (S_ISLNK(m))
		return ("l");
	else if (S_ISSOCK(m))
		return ("s");
	else
		return ("-");
}

void		print_right(mode_t st_mode)
{
	ft_putstr(print_type(st_mode));
	ft_putstr((st_mode & S_IRUSR) ? "r" : "-");
	ft_putstr((st_mode & S_IWUSR) ? "w" : "-");
	if (st_mode & S_ISUID)
		ft_putstr((st_mode & S_IXUSR) ? "s" : "S");
	else
		ft_putstr((st_mode & S_IXUSR) ? "x" : "-");
	ft_putstr((st_mode & S_IRGRP) ? "r" : "-");
	ft_putstr((st_mode & S_IWGRP) ? "w" : "-");
	if (st_mode & S_ISGID)
		ft_putstr((st_mode & S_IXGRP) ? "s" : "S");
	else
		ft_putstr((st_mode & S_IXGRP) ? "x" : "-");
	ft_putstr((st_mode & S_IROTH) ? "r" : "-");
	ft_putstr((st_mode & S_IWOTH) ? "w" : "-");
	if ((st_mode & S_ISVTX))
		ft_putstr((st_mode & S_IXOTH) ? "t" : "T");
	else
		ft_putstr((st_mode & S_IXOTH) ? "x" : "-");
	ft_putchar(' ');
}

void		print_basic(t_ls meta, t_reader *current, int root)
{
	if (!meta.arg.a && (!ft_strcmp(current->name, ".")
		|| !ft_strcmp(current->name, "..") || (current->name[0] == '.')))
		return ;
	color_name(current);
	if (current->next && !(root && is_next_dir(current)))
		ft_putchar('\t');
	else if (current->next || meta.arg.br)
		ft_putstr("\n\n");
	else
		ft_putchar('\n');
}

void		print_time(t_reader *current)
{
	char	*date;
	char	*hour;
	char	*year;
	char	*temps;
	time_t	now;

	temps = ctime(&current->sb.st_mtime);
	temps = ft_strsub(temps, 0, _LEN(temps) - 1);
	now = time(0);
	date = ft_strndup(&temps[4], 7);
	hour = ft_strndup(&temps[11], 5);
	year = ft_strndup(&temps[20], 4);
	ft_putstr(date);
	if (current->sb.st_mtime <= now - _SIXMONTH)
		ft_putstr(year);
	else
		ft_putstr(hour);
	ft_strdel(&temps);
	ft_strdel(&date);
	ft_strdel(&hour);
	ft_strdel(&year);
}
