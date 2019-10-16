/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:44:16 by cylemair          #+#    #+#             */
/*   Updated: 2019/10/16 19:57:03 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char		*concat(char *error, char *name, t_ls *meta)
{
	char	*new;
	char	*tmp;

	if (!(*meta).error_sd)
	{
		(*meta).error_sd = 1;
		tmp = ft_strjoin((char const *)name, (char const *)error);
		new = ft_strjoin((char const *)_OPEN, (char const *)tmp);
		ft_strdel(&tmp);
		return (new);
	}
	else
		(*meta).error_sd = 0;
	return (NULL);
}

char		**stat_error(char **out, char **array, int index, char *str,
						t_ls *meta)
{
	char	*new;
	char	*name;

	name = ft_strdup((str) ? str : array[index]);
	new = NULL;
	if (errno == EACCES)
		new = concat(_ACCES, name, meta);
	else if (errno == EBADF)
	{
		new = concat(_BAD_FD, name, meta);
	}
	else if (errno == ELOOP)
	{
		new = concat(_LOOP, name, meta);
	}
	else if (errno == ENAMETOOLONG)
		new = concat(_TOOLONG, name, meta);
	else if (errno == ENOENT)
	{
		new = concat(_UNKNOW, name, meta);
	}
	else if (errno == ENOMEM)
		new = concat(_NOMEM, name, meta);
	if (new)
	{
		out = (!out) ? create_array(new) : array_add(out, new);
		ft_strdel(&new);
		ft_strdel(&name);
	}
	return (out);
}

char		**d_error(char **out, char **array, int index, char *str,
						t_ls *meta)
{
	char	*new;
	char	*name;

	name = ft_strdup((str) ? str : array[index]);
	new = NULL;
	if (errno == EACCES)
		new = concat(_ACCES, name, meta);
	else if (errno == ELOOP)
	{
		new = concat(_LOOP, name, meta);
	}
	else if (errno == ENAMETOOLONG)
		new = concat(_TOOLONG, name, meta);
	else if (errno == ENOENT)
	{
		new = concat(_UNKNOW, name, meta);
	}
	else if (errno == ENOMEM)
		new = concat(_NOMEM, name, meta);
	else if (errno == ENOTDIR)
		new = concat(_NOTDIR, name, meta);
	if (new)
	{
		out = (!out) ? create_array(new) : array_add(out, new);
		ft_strdel(&new);
		ft_strdel(&name);
	}
	return (out);
}

void		output_error(char const **out)
{
	int		i;

	i = 0;
	RED("");
	while (out && out[i])
	{
		_PL(out[i]);
		i++;
	}
	RESET();
}
