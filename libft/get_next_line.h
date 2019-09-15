/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 18:26:07 by cylemair          #+#    #+#             */
/*   Updated: 2019/01/11 18:26:08 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 4

# include <fcntl.h>
# include <unistd.h>

int			get_next_line(const int fd, char **line);
char		*str_join_free(char **s1, char **s2);

#endif
