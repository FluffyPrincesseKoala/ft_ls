/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:29:03 by cylemair          #+#    #+#             */
/*   Updated: 2018/12/19 16:29:03 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

static size_t	digit_count(long n)
{
	size_t i;

	i = 1;
	if (n < 0)
		n = -n;
	while (n >= 10)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	long		v;
	size_t		count;
	char		*str;
	char		sig;

	v = n;
	sig = (v < 0 ? 1 : 0);
	count = digit_count(v);
	str = ft_strnew(count + sig);
	if (str == NULL)
		return (NULL);
	if (sig)
	{
		v = -v;
		str[0] = '-';
	}
	while (count > 0)
	{
		str[count + sig - 1] = (v % 10) + '0';
		count--;
		v /= 10;
	}
	return (str);
}
