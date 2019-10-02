/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:13:59 by cylemair          #+#    #+#             */
/*   Updated: 2019/10/02 20:12:48 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char		*str_add_delim(char *dest, char *str, char delim) // unused
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
	int		len;
	int		new_len;

	if (!str || !(new = malloc(sizeof(char*) * 2)))
		return (NULL);
	if ((len = ft_strlen(str) - 1) == (new_len = strlen_rdelim(str, '/'))
		&& len >= 1)
		new[0] = ft_strndup(str, new_len);
	else
		new[0] = ft_strdup(str);
	new[1] = NULL;
	return (new);
}

char		*ft_strndup(const char *str, int len)
{
	char	*new;
	int		i;

	i = 0;
	if (!(new = malloc(sizeof(char) * (len))))
		return (NULL);
	while (str && str[i] && i != len)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char		**array_add(char** array, char *add)
{
	char	**new;
	char	i;
	int		len;
	int		new_len;

	i = array_len(array);
	if (!i || !(new = malloc(sizeof(char*) * (i + 2))))
		return ((array) ? array : NULL);
	i = 0;
	while (array[i])
	{
		if ((len = ft_strlen(array[i]) - 1) == (new_len = strlen_rdelim(array[i], '/'))
			&& len >= 1)
			new[i] = ft_strndup(array[i], new_len);
		new[i] = ft_strdup(array[i]);
		i++;
	}
	if ((len = ft_strlen(add) - 1) == (new_len = strlen_rdelim(add, '/'))
		&& len >= 1)
		new[i] = ft_strndup(add, new_len);
	else
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
			x++;
		}
		if (is_opt && !(new.arg._l || new.arg._R || new.arg._a || new.arg._r
			|| new.arg._t))
		{
			PR("invalid option", av[y]);
			exit(-1);
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

void		print_arg(t_ls meta) // debug
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

void				dsy(t_ls meta) // debug
{
	t_reader		*cur;
	t_reader		*sub;
	t_reader		*ssub;

	cur = meta.file;
	while (cur)
	{
		PUT("\t");
		PUT(cur->name);
		PUT("\n");
		if (cur->sub)
		{
			sub = cur->sub;
			while (sub)
			{
				PUT("\t\t");
				PUT(sub->name);
				PUT("\n");
				if (sub->sub)
				{
					ssub = sub->sub;
					while (ssub)
					{
						PUT("\t\t\t");
						PUT(ssub->name);
						PUT("\n");
						ssub = ssub->next;
					}
				}
				sub = sub->next;
			}
		}
		cur = cur->next;
	}
}

int					strlen_rdelim(const char *str, int c)
{
	int				i;

	i = ft_strlen(str) - 1;
	while (str[i] && i)
	{
		if (str[i] == c)
			return (i);
		i--;
	}
	return (i);
}

char				**check_last(char **array)
{
	char			**new;
	int				i;
	int				new_len;
	int				len;

	i = 0;
	if (!(new = malloc(sizeof(char) * array_len(array))))
		return (NULL);
	while (array && array[i])
	{		
		if ((len = ft_strlen(array[i]) - 1) == (new_len = strlen_rdelim(array[i], '/'))
			&& len >= 1)
			new[i] = ft_strndup(array[i], new_len);
		else
			new[i] = ft_strdup(array[i]);
		i++;
	}
	new[i] = NULL;
	while (i--)
		free(array[i]);
	free(array);
	return (new);
}

int					main(int ac, char **av)
{
	t_ls			meta;

	meta = set_arg(init_arg(), av);
	if (meta.array == NULL)
		meta.array = create_array(".");
	// else
	// 	meta.array = check_last(meta.array);
	print_arg(meta);

	meta.file = open_directory(meta);

	// // dsy(meta);
	// // RED("BEFOR_SORTING\n");
	// // RESET();
	// // reader_sub(meta.file);
	PUT("\n\n");
	RED("AFTER_SORTING_BY_NAME\n_____________________\n");
	RESET();

//	choose sorting

	if (meta.arg._r)
	{
		if (meta.arg._t)
			sort_map(&meta.file, &rcmp_time);
		else
			sort_map(&meta.file, &rcmp_name);
	}
	else
	{
		if (meta.arg._t)
			sort_map(&meta.file, &cmp_time);
		else
			sort_map(&meta.file, &cmp_name);
	}
	reader(meta, meta.file, meta.file, 1);
	// if (!meta.arg._l)
	// 	ft_putchar('\n');
	// RED("AFTER_SORTING_BY_TIME\n");
	// RESET();
	// sort_map(&meta.file, &cmp_time);
	// reader_sub(meta.file, meta.file);
}
