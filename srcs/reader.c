/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 12:34:58 by cylemair          #+#    #+#             */
/*   Updated: 2019/10/15 21:20:21 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int					link_or_not(const char *path, struct stat *sb, t_ls meta)
{
	if (meta.arg.l)
	{
		return (lstat(path, sb));
	}
	else
		return (stat(path, sb));
}

t_reader			*go_sub(struct dirent *dir, t_ls *meta, char *new, int i)
{
	DIR		*sub;

	if (!(*meta).arg.br)
		return (NULL);
	if (!ft_strcmp(dir->d_name, ".") || !ft_strcmp(dir->d_name, ".."))
		return (NULL);
	if (!(sub = opendir(new)))
		(*meta).err = d_error((*meta).err, (*meta).array, i, new);
	else
		return (read_directory(sub, new, meta, i));
	return (NULL);
}

t_reader			*read_directory(DIR *space, char *path, t_ls *meta, int i)
{
	t_reader		*r[2];
	struct dirent	*dir;
	struct stat		sb;
	char			*new;

	ft_memset(r, 0, sizeof(t_reader*) * 2);
	while (space && (dir = readdir(space)))
	{
		(*meta).array_len = A_LEN((*meta).err);
		if (ft_strncmp(dir->d_name, ".", 1) || (*meta).arg.a)
		{
			new = ft_strjoin_free(path, ft_strjoin("/", dir->d_name), 2);
			if (new && link_or_not(new, &sb, *meta))
				(*meta).err = stat_error((*meta).err, (*meta).array, i, new);
			if (new && A_LEN((*meta).err) == (*meta).array_len)
			{
				r[1] = append(&(r[0]), create(sb, (char*)dir->d_name, new));
				if (S_ISDIR(sb.st_mode))
					(r[1])->sub = go_sub(dir, meta, new, i);
			}
			ft_strdel(&new);
		}
	}
	closedir(space);
	return (r[0]);
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
		if (link_or_not((char*)(*meta).array[i], &sb, *meta))
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
