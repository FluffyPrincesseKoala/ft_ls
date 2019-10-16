/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:13:59 by cylemair          #+#    #+#             */
/*   Updated: 2019/10/16 19:57:07 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int					main(int ac, char **av)
{
	t_ls			meta;

	(void)ac;
	meta = set_arg(init_arg(), av);
	if (meta.array == NULL)
		meta.array = create_array(".");
	meta.file = open_directory(&meta);
	if (meta.file)
	{
		choose_sorting(&meta);
		reader(meta, meta.file, meta.file, 1);
	}
	output_error((char const **)meta.err);
	free_meta(&meta);
	return (0);
}
