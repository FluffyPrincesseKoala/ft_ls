/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 17:36:31 by princesse         #+#    #+#             */
/*   Updated: 2019/10/14 16:54:01 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void				free_reader(t_reader *current)
{
	if (current)
	{
		if (current->sub)
			free_reader(current->sub);
		if (current->next)
			free_reader(current->next);
		free(current->name);
		free(current->path);
		free(current);
	}
}

void				free_meta(t_ls *meta)
{
	if ((*meta).file)
		free_reader((*meta).file);
	free_array((*meta).array);
	free_array((*meta).err);
}
