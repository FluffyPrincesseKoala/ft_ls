/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:13:59 by cylemair          #+#    #+#             */
/*   Updated: 2019/10/11 17:47:42 by cylemair         ###   ########.fr       */
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
	if (array_len(meta._err) > 0
		&& array_len(meta._err) == array_len(meta.array) && !meta.arg._R)
	{
		output_error((char const **)meta._err);
		free_meta(&meta);
		exit(errno);
	}
	choose_sorting(&meta);
	reader(meta, meta.file, meta.file, 1);
	output_error((char const **)meta._err);
	free_meta(&meta);
}
