/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 19:57:11 by cylemair          #+#    #+#             */
/*   Updated: 2019/10/02 20:03:48 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void			swap_data(t_reader **a, t_reader **b)
{
	struct s_reader	*c;
	struct dirent	*dir;
	struct stat		sb;
	char			*path;
	char			*name;

	c = ((*a)->sub);
	dir = ((*a)->dir);
	sb = ((*a)->sb);
	path = ((*a)->path);
	name = ((*a)->name);
	
	((*a)->sub) = ((*b)->sub);
	((*a)->dir) = ((*b)->dir);
	((*a)->sb) = ((*b)->sb);
	((*a)->path) = ((*b)->path);
	((*a)->name) = ((*b)->name);

	((*b)->sub) = c;
	((*b)->dir) = dir;
	((*b)->sb) = sb;
	((*b)->path) = path;
	((*b)->name) = name;
}

int				cmp_name(t_reader *a, t_reader *b)
{
	return (ft_strcmp(a->name, b->name));
}

int				cmp_time(t_reader *a, t_reader *b)
{
	if ((int)a->sb.st_mtime > (int)b->sb.st_mtime)
		return (1);
	if ((int)a->sb.st_mtime == (int)b->sb.st_mtime)
		return (cmp_name(a, b));
	return (-1);
}

int				rcmp_name(t_reader *a, t_reader *b)
{
	if (ft_strcmp(a->name, b->name) > 0)
		return (-1);
	if (ft_strcmp(a->name, b->name) < 0)
		return (1);
	return (0);
}

int				rcmp_time(t_reader *a, t_reader *b)
{
	if ((int)a->sb.st_mtime > (int)b->sb.st_mtime)
		return (-1);
	if ((int)a->sb.st_mtime == (int)b->sb.st_mtime)
		return (rcmp_name(a, b));
	return (1);
}

void			sort_map(t_reader **file, int (*f)(t_reader *, t_reader *))
{
	t_reader	*head;
	t_reader	*current;
	int			swaped;

	head = *file;
	while (head)
	{
		swaped = 0;
		current = head->next;
		if (head->sub)
		{
			sort_map(&head->sub, (*f));
		}
		while (current && !swaped)
		{
			if ((*f)(head, current) > 0)
			{
				swap_data(&head, &current);
				swaped = 1;
			}
			current = current->next;
		}
		if (!current && !swaped)
			head = head->next;
	}
}