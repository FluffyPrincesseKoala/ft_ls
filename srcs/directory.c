/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 17:17:25 by cylemair          #+#    #+#             */
/*   Updated: 2019/10/15 12:34:42 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int					is_full(t_reader *current)
{
	int				check;

	check = 0;
	if (current)
	{
		check += is_full(current->next);
		if (ft_strcmp(current->name, ".") && ft_strcmp(current->name, ".."))
			return (1);
	}
	return (check);
}

int					is_next_dir(t_reader *current)
{
	t_reader		*tmp;

	tmp = current->next;
	if (tmp && tmp->sub)
		return (1);
	return (0);
}

int					get_total(t_reader *current)
{
	if (current->next)
		return ((current->sb.st_blocks / 2) + get_total(current->next));
	return (current->sb.st_blocks / 2);
}
