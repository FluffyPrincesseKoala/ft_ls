/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:29:59 by cylemair          #+#    #+#             */
/*   Updated: 2018/12/19 16:29:59 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cur;
	int				i;

	cur = (unsigned char*)s;
	i = 0;
	while (n--)
	{
		if (cur[i] == (unsigned char)c)
			return (&cur[i]);
		i++;
	}
	return (NULL);
}
