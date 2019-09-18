/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: princesse <princesse@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:13:59 by cylemair          #+#    #+#             */
/*   Updated: 2019/09/16 03:18:51 by princesse        ###   ########.fr       */
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

t_opt		set_arg(t_opt arg, char **av)
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
		is_path = (av[y][x] != '-') ? 1 : is_path;
		if (is_path)
			arg.path = (arg.path) ? str_add_delim(arg.path, av[y], ':') : ft_strdup(av[y]);
		while (av[y][x] && !is_path)
		{
			is_opt = (av[y][x] == '-') ? 1 : is_opt;
			arg = (is_opt) ? read_arg(arg, av[y][x]) : arg;
			x += 1;
		}
		y += 1;
	}
	return (arg);
}

t_opt		init_arg()
{
	t_opt	arg;

	arg._l = 0;
	arg._R = 0;
	arg._a = 0;
	arg._r = 0;
	arg._t = 0;
	arg.path = NULL;
	return (arg);
}

void		print_arg(t_opt arg)
{
	if (arg._l == 1) {
		GREEN("-l ");
	} else {
		RED("-l ");
	} if (arg._R == 1) {
		GREEN("-R ");
	} else {
		RED("-R ");
	} if (arg._a == 1) {
		GREEN("-a ");
	} else {
		RED("-a ");
	} if (arg._r == 1) {
		GREEN("-r ");
	} else {
		RED("-r ");
	} if (arg._t == 1) {
		GREEN("-t ");
	} else {
		RED("-t ");
	}
	CYAN(arg.path);
	ft_putchar('\n');
}

// void		print_dirent(DIR *directory)
// {
// 	struct dirent	*dir;
// 	while (directory && (dir = readdir(directory)))
// 	{
// 		GREEN("");
// 		printf("\ninœud %d\nlen %hu\ntype %u\nname %s\n\n",
// 				dir->d_ino, dir->d_reclen, dir->d_type, dir->d_name);
// 	}
// 	RESET();
// }

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

void 				free_reader(t_reader *file)
{
	if (file->next)
		free_reader(file->next);
	if (file->sub)
		free_reader(file->sub);
	free(file);
}

void				free_meta(t_ls meta)
{
	int				i;

	i = 0;
	free(meta.arg.path);
	while (meta.array[i])
		free(meta.array[i++]);
	free(meta.array);
	free_reader(meta.file);
}

int					main(int ac, char **av)
{
	t_ls			meta;

	meta.arg = set_arg(init_arg(), av);
	print_arg(meta.arg);

	meta.array = ft_strsplit(meta.arg.path, ':');
	meta.file = open_directory(meta);

	GREEN("BEFOR_SORTING\n");
	RESET();
	_READ(meta.file);

	free_meta(meta);
	/*
	GREEN("AFTER_SORTING_BY_NAME\n");
	RESET();
	sort_map(&meta.file, &cmp_name);
	_READ(meta.file);

	GREEN("AFTER_SORTING_BY_TIME\n");
	RESET();
	sort_map(&meta.file, &cmp_time);
	_READ(meta.file);*/
}
