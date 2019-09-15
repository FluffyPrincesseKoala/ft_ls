/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: princesse <princesse@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 22:20:38 by princesse         #+#    #+#             */
/*   Updated: 2019/09/10 16:24:01 by princesse        ###   ########.fr       */
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