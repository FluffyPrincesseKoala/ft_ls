/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 17:17:25 by cylemair          #+#    #+#             */
/*   Updated: 2019/10/14 18:28:41 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int					is_full(t_reader *current)
{
	int				check;

	check = 0;
	if (current)
	{
		check += is_full(current->next);
		if (ft_strcmp(current->name, ".") && ft_strcmp(current->name, ".."))
			return (1);
	}
	return (check);
}

int					is_next_dir(t_reader *current)
{
	t_reader		*tmp;

	tmp = current->next;
	if (tmp && tmp->sub)
		return (1);
	return (0);
}

int					get_total(t_reader *current)
{
	if (current->next)
		return ((current->sb.st_blocks / 2) + get_total(current->next));
	return (current->sb.st_blocks / 2);
}

t_reader			*read_directory(DIR *space, char *path, t_ls *meta, int i)
{
	t_reader		*tmp;
	t_reader		*head;
	DIR				*sub;
	struct dirent	*dir;
	struct stat		sb;
	char			*new_path;
	char			*tmp_path;

	head = NULL;
	while (space && (dir = readdir(space)))
	{
		(*meta).array_len = A_LEN((*meta).err);
		if (ft_strncmp(dir->d_name, ".", 1) || (*meta).arg.a)
			new_path = ft_strjoin(path, ((tmp_path = ft_strjoin("/", dir->d_name))));
		if (new_path && lstat(new_path, &sb))
			(*meta).err = stat_error((*meta).err, (*meta).array, i, new_path);
		if (new_path && A_LEN((*meta).err) == (*meta).array_len)
		{
			tmp = append(&head, create(sb, (char*)dir->d_name, new_path));
			if ((S_ISDIR(sb.st_mode) && ft_strcmp(dir->d_name, ".")
				&& ft_strcmp(dir->d_name, "..")) && (*meta).arg.br && !(sub = opendir(new_path)))
			{
				(*meta).err = d_error((*meta).err, (*meta).array, i, new_path);
			}
			else if (((S_ISDIR(sb.st_mode) && ft_strcmp(dir->d_name, ".")
				&& ft_strcmp(dir->d_name, "..")) && (*meta).arg.br))
				tmp->sub = read_directory(sub, new_path, meta, i);
		}
		ft_strdel(&new_path);
		ft_strdel(&tmp_path);
	}
	closedir(space);
	return (head);
}

t_reader			*open_directory(t_ls *meta)
{
	DIR				*buff;
	struct stat		sb;
	int				i;
	t_reader		*new;
	t_reader		*head;

	i = -1;
	head = NULL;
	new = NULL;
	while ((*meta).array[++i])
	{
		(*meta).array_len = A_LEN((*meta).err);
		if (lstat((char*)(*meta).array[i], &sb))
			(*meta).err = stat_error((*meta).err, (*meta).array, i, NULL);
		if (!(buff = opendir((*meta).array[i])) && (S_ISDIR(sb.st_mode)))
			(*meta).err = d_error((*meta).err, (*meta).array, i, NULL);
		if (A_LEN((*meta).err) == (*meta).array_len)
		{
			new = append(&head, create(sb, (*meta).array[i], (*meta).array[i]));
			new = ((S_ISDIR(sb.st_mode))
			|| (S_ISDIR(sb.st_mode) && (*meta).arg.br)) ? append(&new->sub,
			read_directory(buff, (*meta).array[i], meta, i)) : new;
		}
	}
	return (head);
}
