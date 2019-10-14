/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:13:16 by cylemair          #+#    #+#             */
/*   Updated: 2019/10/14 14:50:33 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int				strlen_rdelim(const char *str, int c)
{
	int			i;

	i = ft_strlen(str) - 1;
	while (str && i && str[i])
	{
		if (str[i] == c)
			return (i);
		i--;
	}
	return (i);
}

char			*ft_strndup(const char *str, int len)
{
	char		*new;
	int			i;

	i = 0;
	if (!(new = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (str && str[i] && i != len)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
