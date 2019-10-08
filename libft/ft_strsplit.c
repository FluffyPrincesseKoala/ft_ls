/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:37:46 by cylemair          #+#    #+#             */
/*   Updated: 2018/12/19 16:37:46 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_copy_str(char const *s, char c, size_t size_a, char **ret)
{
	size_t		i;
	size_t		len_str;

	i = 0;
	len_str = 0;
	while (i < size_a)
	{
		if (*s != c && *s != '\0')
			len_str++;
		else if (len_str)
		{
			if ((ret[i] = (char *)malloc(sizeof(**ret) * len_str + 1)) == NULL)
				return (1);
			ft_strncpy(ret[i], s - len_str, len_str);
			ret[i++][len_str] = '\0';
			len_str = 0;
		}
		s++;
	}
	return (0);
}

static size_t	ft_get_size_a(char const *s, char c)
{
	size_t		size_a;
	char const	*temp_s;

	size_a = 0;
	temp_s = s;
	while (*temp_s != '\0')
	{
		if (*temp_s != c && (*(temp_s - 1) == c || (temp_s - 1) < s))
			size_a++;
		temp_s++;
	}
	return (size_a);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**ret;
	size_t		size_a;

	if (s == NULL)
		return (NULL);
	size_a = ft_get_size_a(s, c);
	ret = (char **)malloc(sizeof(*ret) * (size_a + 1));
	if (ret == NULL)
		return (NULL);
	if (ft_copy_str(s, c, size_a, ret))
		return (NULL);
	ret[size_a] = NULL;
	return (ret);
}
