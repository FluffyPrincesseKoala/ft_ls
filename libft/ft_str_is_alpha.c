/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 19:31:50 by cylemair          #+#    #+#             */
/*   Updated: 2019/06/11 19:31:50 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_is_alpha(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!isalpha((int)str[i]))
			return (0);
		i += 1;
	}
	if (str)
		return (1);
}
