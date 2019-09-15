/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:33:27 by cylemair          #+#    #+#             */
/*   Updated: 2018/12/19 16:33:28 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1 && s1[i])
		i++;
	while (s2 && s2[j])
		j++;
	if ((new = malloc(sizeof(char) * (i + j + 1))) == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		new[i] = (char)s1[i];
		i += 1;
	}
	while (s2 && s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}
