/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:38:08 by cylemair          #+#    #+#             */
/*   Updated: 2018/12/19 16:38:08 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*new;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (!s || !(new = ft_strnew(len)))
		return (NULL);
	while (s[j] && j != start)
		j += 1;
	if (s[j] == s[start])
	{
		while (i != len)
		{
			new[i] = (char)s[j];
			j += 1;
			i += 1;
		}
		new[i] = 0;
		return (new);
	}
	return (NULL);
}
