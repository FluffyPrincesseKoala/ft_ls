/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: princesse <princesse@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 15:24:04 by cylemair          #+#    #+#             */
/*   Updated: 2019/09/19 21:15:39 by princesse        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
//# include <attr/xattr.h>
# include <time.h>
# include <stdio.h>
# include <unistd.h>
#include <errno.h>

# define _LEN(STR)		ft_strlen(STR)
# define A_LEN(ARRAY)	array_len(ARRAY)
# define IS_DIR(F, D)	(S_ISDIR(F.st_mode) 			\
						&& ft_strcmp(D->d_name, ".")	\
						&& ft_strcmp(D->d_name, ".."))
# define P_BASIC(FILE)	ft_putstr(FILE->name)
# define _DIR(NAME) 	ft_putendl(ft_strcat(NAME, ":"));
# define _UNKNOW 		"No such file or directory\n"
# define _PL(X)			ft_putendl(X);
# define PUT(X)			ft_putstr(X);
# define PN(X)			ft_putnbr(X);
# define _READ(X)		reader(X, X)
# define RED(X) 		ft_putstr("\033[1;31m"); \
						ft_putstr(X);
# define GREEN(X) 		ft_putstr("\033[0;32m"); \
						ft_putstr(X);
# define BLUE(X) 		ft_putstr("\033[0;34m"); \
						ft_putstr(X);
# define CYAN(X) 		ft_putstr("\033[0;36m"); \
						ft_putstr(X);
# define RESET() 		ft_putstr("\033[0m")
# define PR(NAME, E)	ft_putstr("\033[1;31m");	\
						ft_putstr_fd("ls: ", 2);	\
						ft_putstr_fd(NAME, 2);		\
						ft_putstr_fd(": ", 2);		\
						ft_putstr_fd(E, 2);			\
						RESET();

typedef struct		s_opt
{
	int				_l;
	int				_R;
	int				_a;
	int				_r;
	int				_t;
}					t_opt;

typedef struct		s_reader
{
	struct stat		sb;
	struct dirent	*dir;
	char			*name;
	char			*path;
	struct s_reader	*next;
	struct s_reader	*sub;
}					t_reader;

typedef struct		s_ls
{
	t_opt			arg;
	t_reader		*file;
	char			**array;
}					t_ls;

int			array_len(char **array);
void		free_array(char **array);
t_reader	*open_directory(t_ls meta);
t_reader	*read_directory(DIR *directory, char *path);
void		reader(t_reader *current, t_reader *head);
void		reader_sub(t_reader *current, t_reader *head);
t_reader    *create(struct stat	sb, char *name, char *path);
t_reader    *lst_append(t_reader **head, t_reader *last);
void		sort_map(t_reader **file, int (*f)(t_reader *, t_reader *));
int			cmp_name(t_reader *a, t_reader *b);
int			cmp_time(t_reader *a, t_reader *b);
void		print_right(mode_t	st_mode);

#endif