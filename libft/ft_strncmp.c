/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:34:36 by cylemair          #+#    #+#             */
/*   Updated: 2018/12/19 16:34:36 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n)
	{
		while (n-- && (unsigned char *)s1 && (unsigned char *)s2 &&
			(unsigned char)*s1 && (unsigned char)*s2)
		{
			if ((unsigned char)*s1 != (unsigned char)*s2)
				return ((unsigned char)*s1 - (unsigned char)*s2);
			if (n)
			{
				s1++;
				s2++;
			}
		}
		if (((unsigned char)*s1 || (unsigned char)*s2) ||
			((unsigned char)*s1 != (unsigned char)*s2))
			return ((unsigned char)*s1 - (unsigned char)*s2);
	}
	return (0);
}
