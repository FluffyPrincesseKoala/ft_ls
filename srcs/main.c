/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:13:59 by cylemair          #+#    #+#             */
/*   Updated: 2019/10/15 16:03:16 by cylemair         ###   ########.fr       */
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
	if (array_len(meta.err) > 0
		&& array_len(meta.err) == array_len(meta.array) && !meta.arg.br)
	{
		output_error((char const **)meta.err);
		free_meta(&meta);
		exit(errno);
	}
	choose_sorting(&meta);
	reader(meta, meta.file, meta.file, 1);
	output_error((char const **)meta.err);
	free_meta(&meta);
	//while (1);
}
