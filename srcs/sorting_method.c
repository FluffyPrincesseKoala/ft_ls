/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_method.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 00:10:42 by cylemair          #+#    #+#             */
/*   Updated: 2019/10/14 16:41:39 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void			sort_map(t_reader **file, int (*f)(t_reader *, t_reader *))
{
	t_reader	*head;
	t_reader	*current;

	head = *file;
	while (head)
	{
		current = head->next;
		while (current)
		{
			if ((*f)(head, current) > 0)
				swap_data(&head, &current);
			current = current->next;
		}
		if (!current)
		{
			if (head->sub && !head->sub->sort)
				sort_map(&head->sub, (*f));
			head->sort = 1;
			head = head->next;
		}
	}
}

void			choose_sorting(t_ls *meta)
{
	if ((*meta).arg.r)
	{
		if ((*meta).arg.t)
			sort_map(&(*meta).file, &rcmp_time);
		else
			sort_map(&(*meta).file, &rcmp_name);
	}
	else
	{
		if ((*meta).arg.t)
			sort_map(&(*meta).file, &cmp_time);
		else
			sort_map(&(*meta).file, &cmp_name);
	}
}
