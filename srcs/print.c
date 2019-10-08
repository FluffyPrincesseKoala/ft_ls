/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 21:36:12 by princesse         #+#    #+#             */
/*   Updated: 2019/10/08 22:28:22 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/ft_ls.h"

/*
**	https://en.wikipedia.org/wiki/Unix_file_types#FIFO_(named_pipe)
**	http://manpagesfr.free.fr/man/man2/stat.2.html
*/

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

void		print_right(mode_t	st_mode)
{
	ft_putstr(print_type(st_mode));
    ft_putstr((st_mode & S_IRUSR) ? "r" : "-");
    ft_putstr((st_mode & S_IWUSR) ? "w" : "-");
    ft_putstr((st_mode & S_ISUID) ? "s" : (st_mode & S_IXUSR) ? "x" : "-");
    ft_putstr((st_mode & S_IRGRP) ? "r" : "-");
    ft_putstr((st_mode & S_IWGRP) ? "w" : "-");
    ft_putstr((st_mode & S_ISGID) ? "s" : (st_mode & S_IXGRP) ? "x" : "-");
    ft_putstr((st_mode & S_IROTH) ? "r" : "-");
    ft_putstr((st_mode & S_IWOTH) ? "w" : "-");
    ft_putstr((st_mode & S_ISVTX) ? "t" : (st_mode & S_IXOTH) ? "x" : "-");
	ft_putchar(' ');
}

void	print_basic(t_ls meta, t_reader *current, int root)
{
	if (!meta.arg._a && (!ft_strcmp(current->name, ".")
		|| !ft_strcmp(current->name, "..") || (current->name[0] == '.' )))
		return;
	PUT(current->name);
	if (current->next && !(root && is_next_dir(current)))
		ft_putchar('\t');
	else if (!current->last || meta.arg._R)
		ft_putstr("\n\n");
	else
		ft_putchar('\n');
}

void    print_l(t_ls meta, t_reader *current)
{
    char	*time;
	time = ctime(&current->sb.st_mtime);
	time = ft_strsub(time, 0, _LEN(time) - 1);

	if (!meta.arg._a && (!ft_strcmp(current->name, ".")
		|| !ft_strcmp(current->name, "..")))
		return;
	print_right(current->sb.st_mode);
	PUT(" ");
	ft_putnbr(current->sb.st_nlink);
	PUT(" ");
	ft_putstr((getpwuid(current->sb.st_uid))->pw_name);
	ft_putchar(' ');
	ft_putstr((getgrgid(current->sb.st_gid))->gr_name);
	ft_putchar(' ');
	ft_putnbr(current->sb.st_size);
	ft_putchar('\t');
	PUT(time);
	PUT(" ");
	CYAN(current->name);
	if (S_ISLNK(current->sb.st_mode))
	{
		char linkname[PATH_MAX];
		ssize_t r = readlink(current->name, linkname, PATH_MAX);
		if (r != -1)
		{
			linkname[r] = '\0';
			PUT(" -> ");
			PUT(linkname);
		}
	}
	PUT("\n");
	RESET();
}

int			get_total(t_reader *current)
{
	if (current->next)
		return ((current->sb.st_blocks/2) + get_total(current->next));
	return (current->sb.st_blocks/2);
}
