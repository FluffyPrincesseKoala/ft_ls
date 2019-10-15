/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 12:34:58 by cylemair          #+#    #+#             */
/*   Updated: 2019/10/15 17:41:54 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int					go_sub(struct stat sb, struct dirent *dir, t_ls *meta)
{
	if (!S_ISDIR(sb.st_mode))
		return 0;
	if (!ft_strcmp(dir->d_name, "."))
		return 0;
	if (!ft_strcmp(dir->d_name, ".."))
		return 0;
	if (!(*meta).arg.br)
		return 0;
	return 1;
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
	new_path = NULL;
	tmp_path = NULL;
	while (space && (dir = readdir(space)))
	{
		(*meta).array_len = A_LEN((*meta).err);
		if (ft_strncmp(dir->d_name, ".", 1) || (*meta).arg.a)
		{
			new_path = ft_strjoin(path, ((tmp_path = ft_strjoin("/", dir->d_name))));
			if (new_path && lstat(new_path, &sb))
				(*meta).err = stat_error((*meta).err, (*meta).array, i, new_path);
			if (new_path && A_LEN((*meta).err) == (*meta).array_len)
			{
				tmp = append(&head, create(sb, (char*)dir->d_name, new_path));
				if (go_sub(sb, dir, meta))
				{
					if (!(sub = opendir(new_path)))
						(*meta).err = d_error((*meta).err, (*meta).array, i, new_path);
					else
						tmp->sub = read_directory(sub, new_path, meta, i);
				}
			}
			ft_strdel(&new_path);
			ft_strdel(&tmp_path);
		}
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
			new = (S_ISDIR(sb.st_mode)) ? append(&new->sub,
			read_directory(buff, (*meta).array[i], meta, i)) : new;
		}
	}
	return (head);
}
