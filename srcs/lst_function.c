/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: princesse <princesse@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 22:08:06 by princesse         #+#    #+#             */
/*   Updated: 2019/09/19 22:24:47 by princesse        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../includes/ft_ls.h"

//void    free_dirent(t_dirent **dir))

// void    free_reader(t_reader **lst)
// {
// 	if ((*lst)->next)
// 		free_reader(&((*lst)->next));
// 	if ((*lst)->sub)
// 		free_reader(&((*lst)->sub));
// 	if ((*lst)->dir)
// 		free_reader(&((*lst)->dir));
// 	ft_memset(*lst, 0, sizeof(t_reader));
// 	free(*lst);
// //    lst = NULL;
// //    free(lst)
// }

t_reader        *create(struct stat	sb, struct dirent *dir, char *path)
{
	t_reader    *new;

	if (!(new = malloc(sizeof(t_reader))))
		return (NULL);
	new->sb = sb;
	new->dir = dir;
	new->name = ft_strdup((char*)dir->d_name);	
	new->path = path;
	new->sub = NULL;
	new->next = NULL;
	return (new);
}

void			reader_sub(t_reader *current, t_reader	*head)
{
	if (current->sub)
	{
		GREEN(current->name);
		PUT("\n");		
		RESET();
		reader(current->sub, current->sub);
	}
	if (current->next)
		reader_sub(current->next, head);
}

void			reader(t_reader *current, t_reader	*head)
{
	char	*time;

	time = ctime(&current->sb.st_mtime);
	time = ft_strsub(time, 0, _LEN(time) - 1);
	CYAN(current->name);
	PUT((_LEN(current->name) > 7) ? "\t" : "\t\t");
	PUT(time);
	PUT("\n");
	RESET();
	if (current->next)
		reader(current->next, head);
	else
	{
		reader_sub(head, head);
	}
	
}

t_reader				*lst_append(t_reader **head, t_reader *last)
{
	t_reader		*tmp;

	if (!*head)
		*head = last;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = last;
	}
	return (last);
}

t_reader			*read_directory(DIR *directory, char *path)
{
	t_reader		*tmp;
	t_reader		*head;
	DIR				*sub;
	struct dirent	*dir;
	struct stat		sb;
	char			*new_path;

	head = NULL;
	new_path = NULL;
	while (directory && (dir = readdir(directory)))
	{
		new_path = ft_strjoin(path, ft_strjoin("/", dir->d_name));
		if ((stat(new_path, &sb)))
		{
			PR(dir->d_name, "permission pas tres autorized\n");
			if (errno == ENOENT)
				PR("errno :", "\n");
		}
		else
		{
			tmp = lst_append(&head, create(sb, dir, path));
			if (IS_DIR(sb, dir)){
				if (!(sub = opendir(new_path)))
					PR(dir->d_name, "SHIT here we go encore\n");
				tmp->sub = read_directory(sub, new_path);
				closedir(sub);
			}
		}
		ft_strdel(&new_path);
	}
	return (head);
}

t_reader			*open_directory(t_ls meta)
{
	struct stat		sb;
	DIR				*buff;
	int				i;
	t_reader		*new;
	t_reader		*head;

	i = 0;
	head = NULL;
	while (meta.array[i])
	{
		if (!(buff = opendir(meta.array[i])) || stat(meta.array[i], &sb))
		{
			PR(meta.array[i], _UNKNOW);
		}
		else
		{
			//head = lst_append(&head, create(sb, dir, meta.array[i]));
			new = lst_append(&head, read_directory(buff, meta.array[i]));
			closedir(buff);			
		}
		i += 1;
	}
	return (new);
}
// sorting

void			swap_data(t_reader **a, t_reader **b)
{
	struct s_reader	*c;
	struct dirent	*dir;
	struct stat		sb;
	char			*path;
	char			*name;

	c = ((*a)->sub);
	dir = ((*a)->dir);
	sb = ((*a)->sb);
	path = ((*a)->path);
	name = ((*a)->name);
	
	((*a)->sub) = ((*b)->sub);
	((*a)->dir) = ((*b)->dir);
	((*a)->sb) = ((*b)->sb);
	((*a)->path) = ((*b)->path);
	((*a)->name) = ((*b)->name);

	((*b)->sub) = c;
	((*b)->dir) = dir;
	((*b)->sb) = sb;
	((*b)->path) = path;
	((*b)->name) = name;
}

int				cmp_name(t_reader *a, t_reader *b)
{
	return (ft_strcmp(a->name, b->name));
}

int				cmp_time(t_reader *a, t_reader *b)
{
	//printf("%s\t\t%zu\t>=\t%s\t\t%zu\n", a->dir->d_name, a->sb.st_mtime, b->dir->d_name, b->sb.st_mtime);
	if ((int)a->sb.st_mtime > (int)b->sb.st_mtime)
		return (1);
	if ((int)a->sb.st_mtime == (int)b->sb.st_mtime)
		return (0);
	return (-1);
}

void			sort_map(t_reader **file, int (*f)(t_reader *, t_reader *))
{
	t_reader	*head;
	t_reader	*current;
	int			swaped;

	head = *file;
	while (head)
	{
		swaped = 0;
		current = head->next;
		while (current && !swaped)
		{
			// printf("(head = %s	<	current = %s) ? %s\n",
			// 	head->dir->d_name, current->dir->d_name,
			// 	((*f)(head, current)) ? "OUI" : "NON");
			if ((*f)(head, current) > 0)
			{
				swap_data(&head, &current);
				swaped = 1;
			}
			current = current->next;
		}
		if (!swaped || !current)
			head = head->next;
	}
}