/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:34:15 by cylemair          #+#    #+#             */
/*   Updated: 2018/12/19 16:34:15 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	char	*ret;
	int		i;

	if (!s || (ret = malloc(sizeof(char) * (ft_strlen(s)) + 1)) == 0)
		return (0);
	i = 0;
	while (s[i])
	{
		ret[i] = f(s[i]);
		i += 1;
	}
	ret[i] = '\0';
	return (ret);
}
