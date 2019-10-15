/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 12:34:58 by cylemair          #+#    #+#             */
/*   Updated: 2019/10/15 13:05:20 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char                *fetch_path(char *path, char *name)
{
	char            *new_path;
	char            *tmp_path;

	tmp_path = ft_strjoin("/", name);
	new_path = ft_strjoin(path, tmp_path);
	ft_strdel(&tmp_path);
	return (new_path);
}

t_reader			*read_directory(DIR *space, char *path, t_ls *meta, int i)
{
	t_reader		*tmp;
	t_reader		*head;
	DIR				*sub;
	struct dirent	*dir;
	struct stat		sb;

	head = NULL;
	while (space && (dir = readdir(space)))
	{
		(*meta).array_len = A_LEN((*meta).err);
		(*meta).new_path = fetch_path(path, dir->d_name);
		if ((*meta).new_path && lstat((*meta).new_path, &sb))
			(*meta).err = stat_error((*meta).err, (*meta).array, i, (*meta).new_path);
		if ((*meta).new_path && A_LEN((*meta).err) == (*meta).array_len)
		{
			tmp = append(&head, create(sb, (char*)dir->d_name, (*meta).new_path));
			if ((DIR_NOT_A(sb.st_mode, dir->d_name)) && (*meta).arg.br
				&& !(sub = opendir((*meta).new_path)))
				(*meta).err = d_error((*meta).err, (*meta).array, i, (*meta).new_path);
			else if ((DIR_NOT_A(sb.st_mode, dir->d_name)) && (*meta).arg.br)
				tmp->sub = read_directory(sub, (*meta).new_path, meta, i);
		}
		ft_strdel(&((*meta).new_path));
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
		if ((S_ISDIR(sb.st_mode)) && !(buff = opendir((*meta).array[i])))
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
