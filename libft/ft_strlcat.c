/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:33:38 by cylemair          #+#    #+#             */
/*   Updated: 2018/12/19 16:33:38 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dest, const char *src, size_t size)
{
	char		*idest;
	const char	*isrc;
	size_t		n;
	size_t		len;

	idest = dest;
	isrc = src;
	n = size;
	while (*idest != '\0' && n-- != 0)
		idest++;
	len = idest - dest;
	n = size - len;
	if (n == 0)
		return (len + ft_strlen(src));
	while (*isrc != '\0')
	{
		if (n != 1)
		{
			*idest++ = *isrc;
			n--;
		}
		isrc++;
	}
	*idest = '\0';
	return (len + (isrc - src));
}
