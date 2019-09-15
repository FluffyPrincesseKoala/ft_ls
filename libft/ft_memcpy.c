/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:29:34 by cylemair          #+#    #+#             */
/*   Updated: 2018/12/19 16:29:34 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					*ft_memcpy(void *s1, const void *s2, size_t n)
{
	unsigned char		*c1;
	const unsigned char	*c2;

	c1 = (unsigned char *)s1;
	c2 = (const unsigned char *)s2;
	while (n)
	{
		*c1++ = *c2++;
		n--;
	}
	return (s1);
}
