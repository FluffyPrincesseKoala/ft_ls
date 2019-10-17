/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 22:08:06 by princesse         #+#    #+#             */
/*   Updated: 2019/10/16 20:23:04 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_reader		*create(struct stat	sb, char *name, char *path)
{
	t_reader	*new;

	if (!(new = malloc(sizeof(t_reader))))
		return (NULL);
	new->sb = sb;
	new->path = ft_strdup(path);
	new->name = ft_strdup(name);
	new->sort = 0;
	new->sub = NULL;
	new->next = NULL;
	return (new);
}

void			reader_sub(t_ls meta, t_reader *current, int root)
{
	if (current->sub)
	{
		if (((array_len(meta.array) > 1 && root) || meta.arg.br)
			&& (is_full(current->sub) || meta.arg.a))
		{
			GREEN(current->path);
			ft_putstr(":\n");
			RESET();
		}
		if (meta.arg.l && (root || meta.arg.br))
		{
			ft_putstr("total ");
			ft_putnbr(get_total(current->sub));
			ft_putchar('\n');
		}
		if (root || meta.arg.br)
		{
			reader(meta, current->sub, current->sub, 0);
		}
	}
	if (current->next)
		reader_sub(meta, current->next, root);
}

void			reader(t_ls meta, t_reader *head, t_reader *current, int root)
{
	if (!(root && current->sub))
	{
		(meta.arg.l) ? print_l(meta, current) : print_basic(meta,
		current, root);
	}
	if (current->next)
	{
		reader(meta, head, current->next, root);
	}
	else
	{
		reader_sub(meta, head, root);
	}
	if (!current->next && !current->sub && !is_next_dir(current)
		&& A_LEN(meta.array) > 1)
		ft_putchar('\n');
}

t_reader		*append(t_reader **head, t_reader *last)
{
	t_reader	*tmp;

	if (!*head)
		*head = last;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = last;
	}
	return (last);
}
