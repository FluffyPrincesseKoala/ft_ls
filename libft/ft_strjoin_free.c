/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:33:27 by cylemair          #+#    #+#             */
/*   Updated: 2019/10/15 21:16:44 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin_free(char *s1, char *s2, int opt)
{
	char *ret;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL || s2 == NULL)
		ret = ((s1 == NULL) ? ft_strdup(s2) : ft_strdup(s1));
	else
	{
		if (!(ret = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
			return (NULL);
		ret = ft_strcpy(ret, s1);
		ret = ft_strcat(ret, s2);
	}
	if ((opt == 1 || opt == 3) && s1 != NULL)
		free(s1);
	if ((opt == 2 || opt == 3) && s2 != NULL)
		free(s2);
	return (ret);
}
