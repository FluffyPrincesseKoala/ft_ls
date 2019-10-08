/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 22:08:06 by princesse         #+#    #+#             */
/*   Updated: 2019/10/08 23:53:47 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/ft_ls.h"

t_reader        *create(struct stat	sb, char *name, char *path)
{
	t_reader    *new;

	if (!(new = malloc(sizeof(t_reader))))
		return (NULL);
	new->sb = sb;
	new->path = ft_strdup(path);
	new->name = ft_strdup(name);
	new->last = 0;
	new->sub = NULL;
	new->next = NULL;
	return (new);
}

int				is_full(t_reader *current)
{
	int			check;

	check = 0;
	if (current)
	{
		check += is_full(current->next);
		if (ft_strcmp(current->name, ".") && ft_strcmp(current->name, ".."))
			return (1);
	}
	return (check);
}

int				is_next_dir(t_reader *current)
{
	t_reader	*tmp;

	tmp = current->next;
	if (tmp && tmp->sub)
		return (1);
	return (0);
}

void			reader_sub(t_ls meta, t_reader *current, int root)
{
	if (current->sub)
	{
		if (((array_len(meta.array) > 1 && root) || meta.arg._R)
			&& (is_full(current->sub) || meta.arg._a))
		{
			GREEN(current->path);
			PUT(":\n");
			RESET();
		}
		if (meta.arg._l && (root || meta.arg._R))
		{
			PUT("total ");
			PN(get_total(current->sub));
			PUT("\n");
		}
		if (root || meta.arg._R)
		{
			reader(meta, current->sub, current->sub, 0);
		}
	}
	if (current->next)
		reader_sub(meta, current->next, root);
}

void			reader(t_ls meta, t_reader *head, t_reader *current, int root)
{
	if (!(root && current->sub))
	{
		(meta.arg._l) ? print_l(meta, current) : print_basic(meta, current, root);
	}
	if (current->next)
	{
		reader(meta, head, current->next, root);
	}
	else
	{
		reader_sub(meta, head, root);
	}
	if (!current->next && !current->sub && !is_next_dir(current) && A_LEN(meta.array) > 1)
		PUT("\n");
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

t_reader			*read_directory(DIR *directory, char *path, t_ls *meta, int i)
{
	t_reader		*tmp;
	t_reader		*head;
	DIR				*sub;
	struct dirent	*dir;
	struct stat		sb;
	char			*new_path;

	head = NULL;
	while (directory && (dir = readdir(directory)))
	{
		new_path = ft_strjoin(path, ft_strjoin("/", dir->d_name));
		if (lstat(new_path, &sb))
		{
			(*meta)._err = stat_error((*meta)._err, (*meta).array, i, new_path);
		}
		else
		{
			tmp = lst_append(&head, create(sb, (char*)dir->d_name, new_path));
			if (IS_DIR(sb, dir))
			{
				if (!(sub = opendir(new_path)))
				{
					(*meta)._err = dir_error((*meta)._err, (*meta).array, i, new_path);
				}
				else
					tmp->sub = read_directory(sub, new_path, meta, i);
			}
		}
		ft_strdel(&new_path);
	}
	tmp->last = 1;
	closedir(directory);
	return (head);
}

t_reader			*open_directory(t_ls *meta)
{
	DIR				*buff;
	struct stat		sb;
	int				i;
	t_reader		*new;
	t_reader		*head;

	i = 0;
	head = NULL;
	new = NULL;
	while ((*meta).array[i])
	{
		(*meta).array_len = A_LEN((*meta)._err);
		if (lstat((*meta).array[i], &sb))
			(*meta)._err = stat_error((*meta)._err, (*meta).array, i, NULL);
		if (!(buff = opendir((*meta).array[i])) && S_ISDIR(sb.st_mode))
			(*meta)._err = dir_error((*meta)._err, (*meta).array, i, NULL);
		if (A_LEN((*meta)._err) == (*meta).array_len)
		{
			new = lst_append(&head, create(sb, (*meta).array[i], (*meta).array[i]));
			new = (S_ISDIR(sb.st_mode)) ?
				lst_append(&new->sub, read_directory(buff, (*meta).array[i], meta, i)) : new;
		}
		if ((*meta)._err == NULL)
		{
			PUT("_________________\n");
		}
		i += 1;
	}
	return (head);
}
