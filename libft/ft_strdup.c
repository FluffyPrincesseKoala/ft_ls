/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:32:46 by cylemair          #+#    #+#             */
/*   Updated: 2018/12/19 16:32:47 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *src)
{
	char	*str;
	int		i;

	if (!(str = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1))))
		return (NULL);
	i = 0;
	while (src[i])
	{
		str[i] = src[i];
		i += 1;
	}
	str[i] = '\0';
	return (str);
}
