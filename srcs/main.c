/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: princesse <princesse@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:13:59 by cylemair          #+#    #+#             */
/*   Updated: 2019/09/19 22:14:40 by princesse        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char		*str_add_delim(char *dest, char *str, char delim)
{
	char	*new;
	int		i;
	int		j;

	if (!(ft_strlen(dest) + ft_strlen(str))	|| !(new = malloc(sizeof(char)
		* (ft_strlen(dest) + ft_strlen(str) + 2))))
		return (NULL);
	i = 0;
	j = 0;
	if (dest)
	{
		while (dest[i])
		{
			new[i] = dest[i];
			i++;
		}
		new[i++] = delim;
		ft_strdel(&dest);
	}
	while (str[j])
	{
		new[i++] = str[j++];
	}
	new[i] = '\0';
	return (new);
}

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

char		**create_array(char *str)
{
	char	**new;


	if (!str || !(new = malloc(sizeof(char*) * 2)))
		return (NULL);
	new[0] = ft_strdup(str);
	new[1] = NULL;
	return (new);
}

char		**array_add(char** array, char *add)
{
	char	**new;
	char	i;

	i = 0;
	while (array && array[i])
		i++;
	if (!(new = malloc(sizeof(char*) * (i + 2))))
		return ((array) ? array : NULL);
	i = 0;
	while (array[i])
	{
		new[i] = ft_strdup(array[i]);
		i++;
	}
	new[i] = ft_strdup(add);
	new[++i] = NULL;
	ft_memdel((void**)array);
	return (new);
}

t_ls		set_arg(t_ls new, char **av)
{
	int		i;
	int		y;
	int		x;
	int		is_opt;
	int		is_path;

	y = 1;
	i = 0;
	is_path = 0;
	while (av[y])
	{
		x = 0;
		is_opt = 0;
		if ((is_path = (av[y][x] != '-') ? 1 : is_path))
		{
			new.array = (!new.array) ? create_array(av[y]) : array_add(new.array, av[y]);
		}		
		while (av[y][x] && !is_path)
		{
			is_opt = (av[y][x] == '-') ? 1 : is_opt;
			new.arg = (is_opt) ? read_arg(new.arg, av[y][x]) : new.arg;
			x += 1;
		}
		y += 1;
	}
	return (new);
}

t_ls		init_arg()
{
	t_ls	new;

	new.arg._l = 0;
	new.arg._R = 0;
	new.arg._a = 0;
	new.arg._r = 0;
	new.arg._t = 0;
	new.file = NULL;
	new.array = NULL;
	return (new);
}

void		print_arg(t_ls meta)
{
	if (meta.arg._l == 1) {
		GREEN("-l ");
	} else {
		RED("-l ");
	} if (meta.arg._R == 1) {
		GREEN("-R ");
	} else {
		RED("-R ");
	} if (meta.arg._a == 1) {
		GREEN("-a ");
	} else {
		RED("-a ");
	} if (meta.arg._r == 1) {
		GREEN("-r ");
	} else {
		RED("-r ");
	} if (meta.arg._t == 1) {
		GREEN("-t ");
	} else {
		RED("-t ");
	}
	RESET();
	for (int i = 0; meta.array[i]; i++) {
		PUT(meta.array[i]);
		ft_putchar(' ');
	}
	ft_putchar('\n');
}

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
	ft_putstr((S_ISDIR(st_mode)) ? "d" : "-");
    ft_putstr((st_mode & S_IRUSR) ? "r" : "-");
    ft_putstr((st_mode & S_IWUSR) ? "w" : "-");
    ft_putstr((st_mode & S_IXUSR) ? "x" : "-");
    ft_putstr((st_mode & S_IRGRP) ? "r" : "-");
    ft_putstr((st_mode & S_IWGRP) ? "w" : "-");
    ft_putstr((st_mode & S_IXGRP) ? "x" : "-");
    ft_putstr((st_mode & S_IROTH) ? "r" : "-");
    ft_putstr((st_mode & S_IWOTH) ? "w" : "-");
    ft_putstr((st_mode & S_IXOTH) ? "x" : "-");
	ft_putchar(' ');
}

void		print_stat(t_reader *file)
{
	char	*time;

	time = ctime(&file->sb.st_mtime);
	time = ft_strsub(time, 0, _LEN(time) - 1);
	print_right(file->sb.st_mode);
	ft_putnbr(file->sb.st_nlink);
	ft_putchar(' ');
	ft_putstr((getpwuid(file->sb.st_uid))->pw_name);
	ft_putchar(' ');
	ft_putstr((getgrgid(file->sb.st_gid))->gr_name);
	ft_putchar(' ');
	ft_putnbr(file->sb.st_size);
	ft_putchar(' ');
	ft_putstr(time);
	ft_putchar(' ');
	ft_putendl(file->dir->d_name);
}

int					main(int ac, char **av)
{
	t_ls			meta;

	meta = set_arg(init_arg(), av);
	print_arg(meta);

	meta.file = open_directory(meta);

	GREEN("BEFOR_SORTING\n");
	RESET();
	_READ(meta.file);
	
	GREEN("AFTER_SORTING_BY_NAME\n");
	RESET();
	sort_map(&meta.file, &cmp_name);
	_READ(meta.file);

	GREEN("AFTER_SORTING_BY_TIME\n");
	RESET();
	sort_map(&meta.file, &cmp_time);
	_READ(meta.file);
}
