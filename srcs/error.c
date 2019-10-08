/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:44:16 by cylemair          #+#    #+#             */
/*   Updated: 2019/10/09 00:05:08 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char		**stat_error(char **out, char **array, int index, char *_str)
{
	char 	*tmp;
	char 	*new;
	char	*name;

	name = ft_strdup((_str) ? _str : array[index]);
	if (errno == EACCES)
	{
		new = ft_strjoin((char const *)_OPEN, (tmp = ft_strjoin(name, (char const *)_ACCES)));
	}
	else if (errno == ELOOP)
		new = ft_strjoin((char const *)_OPEN, (tmp = ft_strjoin(name, (char const *)_LOOP)));
	else if (errno == ENAMETOOLONG)
		new = ft_strjoin((char const *)_OPEN, (tmp = ft_strjoin(name, (char const *)_TOOLONG)));
	else if (errno == ENOENT)
		new = ft_strjoin((char const *)_OPEN, (tmp = ft_strjoin(name, (char const *)_UNKNOW)));
	else if (errno == ENOMEM)
		new = ft_strjoin((char const *)_OPEN, (tmp = ft_strjoin(name, (char const *)_NOMEM)));
	out = (!out) ? create_array(new) : array_add(out, new);
	ft_strdel(&tmp);
	ft_strdel(&new);
	ft_strdel(&name);
	return (out);
}

char			**dir_error(char **out, char **array, int index, char *_str)
{
	char 	*tmp;
	char 	*new;
	char	*name;

	name = ft_strdup((_str) ? _str : array[index]);
	if (errno == EACCES)
		new = ft_strjoin((char const *)_OPEN, (tmp = ft_strjoin(name, (char const *)_ACCES)));
	else if (errno == ENOENT)
		new = ft_strjoin((char const *)_OPEN, (tmp = ft_strjoin(name, (char const *)_UNKNOW)));
	else if (errno == ENOMEM)
		new = ft_strjoin((char const *)_OPEN, (tmp = ft_strjoin(name, (char const *)_NOMEM)));
	out = (!out) ? create_array(new) : array_add(out, new);
	ft_strdel(&tmp);
	ft_strdel(&new);
	ft_strdel(&name);
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