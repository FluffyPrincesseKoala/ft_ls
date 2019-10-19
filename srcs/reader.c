/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 12:34:58 by cylemair          #+#    #+#             */
/*   Updated: 2019/10/19 20:32:09 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int					is_link(const char *path, struct stat *sb, t_ls meta,
													char *name)
{
	int				ret;

	errno = 0;
	if (meta.arg.l)
	{
		ret = lstat(path, sb);
	}
	else
	{
		ret = lstat(path, sb);
		if (S_ISLNK((*sb).st_mode) && !ft_strcmp(path, name))
			stat(path, sb);
	}
	return (ret);
}

t_reader			*go_sub(struct dirent *dir, t_ls *meta, char *new, int i)
{
	DIR		*sub;

	if (!(*meta).arg.br)
		return (NULL);
	if (!ft_strcmp(dir->d_name, ".") || !ft_strcmp(dir->d_name, ".."))
		return (NULL);
	if (!(sub = opendir(new)))
		(*meta).err = d_error((*meta).err, new, meta);
	else
	{
		return (read_directory(sub, new, meta, i));
	}
	return (NULL);
}

t_reader			*read_directory(DIR *space, char *path, t_ls *meta, int i)
{
	t_reader		*r[2];
	struct dirent	*dir;
	struct stat		sb;
	char			*new;
	int				good;

	ft_memset(r, 0, sizeof(t_reader*) * 2);
	while (space && (dir = readdir(space)))
	{
		good = 0;
		(*meta).array_len = A_LEN((*meta).err);
		if (ft_strncmp(dir->d_name, ".", 1) || (*meta).arg.a)
		{
			new = ft_strjoin_free(path, ft_strjoin("/", dir->d_name), 2);
			if (new && (good = is_link(new, &sb, *meta, dir->d_name)))
				(*meta).err = stat_error((*meta).err, new, meta);
			r[1] = (new && !good) ? append(&(r[0]),
					create(sb, (char*)dir->d_name, new)) : r[1];
			if (S_ISDIR(sb.st_mode) && READ_SUB() && !good)
				(r[1])->sub = go_sub(dir, meta, new, i);
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
	int				good;
	t_reader		*r[2];

	i = -1;
	ft_memset(r, 0, sizeof(t_reader*) * 2);
	while ((*meta).array[++i])
	{
		good = 0;
		(*meta).array_len = A_LEN((*meta).err);
		if ((good = is_link((*meta).array[i], &sb, *meta, (*meta).array[i])))
			(*meta).err = stat_error((*meta).err, (*meta).array[i], meta);
		if ((S_ISDIR(sb.st_mode)) && !(buff = opendir((*meta).array[i])))
			(*meta).err = d_error((*meta).err, (*meta).array[i], meta);
		if (A_LEN((*meta).err) == (*meta).array_len && !good)
		{
			r[1] = append(&(r[0]), create(sb, (*meta).array[i],
							(*meta).array[i]));
			r[1] = (S_ISDIR(sb.st_mode)) ? append(&(r[1])->sub,
			read_directory(buff, (*meta).array[i], meta, i)) : r[1];
		}
	}
	return (r[0]);
}
