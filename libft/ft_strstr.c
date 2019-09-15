/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:37:54 by cylemair          #+#    #+#             */
/*   Updated: 2018/12/19 16:37:54 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strstr(const char *str, const char *to_find)
{
	int		i;
	int		j;

	i = 0;
	if (ft_strlen(to_find) == 0)
		return ((void *)str);
	while (str[i])
	{
		j = 0;
		while (str[i] == to_find[j])
		{
			if (to_find[j + 1] == '\0')
				return ((char *)&str[i - j]);
			i += 1;
			j += 1;
		}
		i = i + 1 - j;
	}
	return (0);
}
