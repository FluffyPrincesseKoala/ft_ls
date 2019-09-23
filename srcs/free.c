/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: princesse <princesse@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 17:36:31 by princesse         #+#    #+#             */
/*   Updated: 2019/09/19 18:18:34 by princesse        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void 				free_reader(t_reader *file)
{
	if (file->next)
		free_reader(file->next);
	if (file->sub)
		free_reader(file->sub);
	free(file);
}

void				free_meta(t_ls meta)
{
	int				i;

	i = 0;
	while (meta.array[i])
		free(meta.array[i++]);
	free(meta.array);
	free_reader(meta.file);
}