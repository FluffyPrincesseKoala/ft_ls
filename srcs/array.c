/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 22:20:38 by princesse         #+#    #+#             */
/*   Updated: 2019/10/08 21:46:53 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int			array_len(char **array)
{
	int		i;

	i = 0;
	while (array && array[i])
	{
		i += 1;
	}
	return (i);
}

void		free_array(char **array)
{
	int		i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		i += 1;
	}
	if (array)
		free(array);
}

char		**create_array(char *str)
{
	char	**new;
	int		len;
	int		new_len;

	if (!str || !(new = malloc(sizeof(char*) * 2)))
		return (NULL);
	if ((len = ft_strlen(str) - 1) == (new_len = strlen_rdelim(str, '/'))
		&& len >= 1)
		new[0] = ft_strndup(str, new_len);
	else
		new[0] = ft_strdup(str);
	new[1] = NULL;
	return (new);
}

char		**array_add(char **array, char *add)
{
	char	**new;
	char	i;
	int		len;
	int		new_len;

	i = array_len(array);
	if (!i || !(new = malloc(sizeof(char*) * (i + 2))))
		return ((array) ? array : NULL);
	i = 0;
	while (array[i])
	{
		if ((len = ft_strlen(array[i]) - 1) == (new_len = strlen_rdelim(array[i], '/'))
			&& len >= 1)
			new[i] = ft_strndup(array[i], new_len);
		new[i] = ft_strdup(array[i]);
		i++;
	}
	if ((len = ft_strlen(add) - 1) == (new_len = strlen_rdelim(add, '/'))
		&& len >= 1)
		new[i] = ft_strndup(add, new_len);
	else
		new[i] = ft_strdup(add);
	new[++i] = NULL;
	ft_memdel((void**)array);
	return (new);
}
