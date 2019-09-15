/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:31:46 by cylemair          #+#    #+#             */
/*   Updated: 2018/12/19 16:31:46 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

inline static void	putlong(long n, int fd)
{
	if (n >= 10)
		putlong(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', fd);
}

void				ft_putnbr_fd(int n, int fd)
{
	long			ln;

	ln = n;
	if (ln < 0)
	{
		ft_putchar_fd('-', fd);
		ln = -ln;
	}
	putlong(ln, fd);
}
