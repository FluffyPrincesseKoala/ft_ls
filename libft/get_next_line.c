/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 14:36:21 by cylemair          #+#    #+#             */
/*   Updated: 2019/03/01 14:36:21 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

char				*str_join_free(char **s1, char **s2)
{
	char			*new;

	if (s1 && s2 && *s1 && *s2)
	{
		if (!(new = malloc(sizeof(char) * (ft_strlen(*s1)
			+ ft_strlen(*s2) + 1))))
			return (NULL);
		new = ft_strcpy(new, *s1);
		new = ft_strcat(new, *s2);
		ft_strdel(s1);
		ft_strdel(s2);
	}
	else if (!*s1)
	{
		new = ft_strdup(*s2);
		ft_strdel(s2);
	}
	else
	{
		new = ft_strdup(*s1);
		ft_strdel(s1);
	}
	return (new);
}

int					fd_parser(const int fd, char **line)
{
	char			buffer[BUFF_SIZE + 1];
	char			*tmp;
	int				ret;

	if ((ret = read(fd, buffer, BUFF_SIZE)) < 0)
		return (-1);
	buffer[ret] = '\0';
	*line = ft_strdup(buffer);
	while (ret > 0 && !(ft_strchr(*line, '\n')))
	{
		if ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
		{
			buffer[ret] = '\0';
			tmp = ft_strdup(buffer);
			*line = str_join_free(line, &tmp);
		}
	}
	return (ret);
}

int					strchri(char *str, char c)
{
	int				i;

	i = 0;
	while (str && str[i] && str[i] != c)
		i++;
	return (i);
}

int					get_next_line(const int fd, char **line)
{
	static	char	*str;
	static	int		ret;
	char			*tmp;

	if (fd <= -1 || line == NULL)
		return (-1);
	if ((ret = fd_parser(fd, line)) <= -1)
		return (-1);
	tmp = str_join_free(&str, line);
	if (ft_strchr(tmp, '\n') && ft_strchr(tmp, '\n') + 1)
		str = ft_strdup(ft_strchr(tmp, '\n') + 1);
	*line = ft_strsub(tmp, 0, strchri(tmp, '\n'));
	ft_strdel(&tmp);
	return ((ft_strlen(*line) || ret || str) ? 1 : ret);
}
