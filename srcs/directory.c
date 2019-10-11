/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 17:17:25 by cylemair          #+#    #+#             */
/*   Updated: 2019/10/11 19:40:05 by cylemair         ###   ########.fr       */
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

t_reader			*read_directory(DIR *directory, char *path,
									t_ls *meta, int i)
{
	VAR();
	head = NULL;
	while (directory && (dir = readdir(directory)))
	{
		ABUSE();
		if (len)
		{
			tmp = append(&head, create(sb, (char*)dir->d_name, len));
			if (IS_DIR(sb, dir) && (*meta).arg._R && !(sub = opendir(len)))
				(*meta)._err = d_error((*meta)._err, (*meta).array, i, len);
			else if (IS_DIR(sb, dir) && (*meta).arg._R)
				tmp->sub = read_directory(sub, len, meta, i);
		}
		ft_strdel(&len);
		ft_strdel(&tmp_path);
	}
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

	i = -1;
	head = NULL;
	new = NULL;
	while ((*meta).array[++i])
	{
		(*meta).array_len = A_LEN((*meta)._err);
		if (lstat((char*)(*meta).array[i], &sb))
			(*meta)._err = stat_error((*meta)._err, (*meta).array, i, NULL);
		if (!(buff = opendir((*meta).array[i])) && S_ISDIR(sb.st_mode))
			(*meta)._err = d_error((*meta)._err, (*meta).array, i, NULL);
		if (A_LEN((*meta)._err) == (*meta).array_len)
		{
			new = append(&head, create(sb, (*meta).array[i], (*meta).array[i]));
			new = ((S_ISDIR(sb.st_mode) && _A((*meta).array[i]))
			|| (S_ISDIR(sb.st_mode) || (*meta).arg._R)) ? append(&new->sub,
			read_directory(buff, (*meta).array[i], meta, i)) : new;
		}
	}
	return (head);
}
