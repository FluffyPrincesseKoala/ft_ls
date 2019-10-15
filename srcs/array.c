/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 22:20:38 by princesse         #+#    #+#             */
/*   Updated: 2019/10/15 14:24:32 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int			array_len(char **array)
{
	int		i;

	i = 0;
	while (array && array[i])
		i += 1;
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
	int		new_len;

	new_len = 0;
	if (!str || !(new = malloc(sizeof(char*) * 2)))
		return (NULL);
	new[0] = ft_strdup(str);
	new[1] = NULL;
	return (new);
}

char		**array_add(char **array, char *add)
{
	char	**new;
	int		i;

	i = array_len(array);
	if ((!i) || !add)
		return (array);
	if (!(new = malloc(sizeof(char*) * (i + 2))))
		return (array);
	i = -1;
	while (array[++i])
		new[i] =  ft_strdup(array[i]);
	new[i] =  ft_strdup(add);
	new[++i] = NULL;
	free_array(array);
	return (new);
}

int			create_or_add(char ***array, char *add)
{
	int		is_path;

	is_path = 0;
	if ((is_path = (add[0] != '-') ? 1 : is_path))
		*array = (!*array) ? create_array(add) : array_add(*array, add);
	return (is_path);
}
