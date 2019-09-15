/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:34:18 by cylemair          #+#    #+#             */
/*   Updated: 2018/12/19 16:34:19 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*new;

	if (!s || !(new = ft_strnew(ft_strlen((char *)s))))
		return (NULL);
	i = 0;
	while (s[i])
	{
		new[i] = (*f)(i, s[i]);
		i += 1;
	}
	new[i] = '\0';
	return (new);
}
