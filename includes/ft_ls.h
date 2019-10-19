/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 15:24:04 by cylemair          #+#    #+#             */
/*   Updated: 2019/10/19 20:09:29 by cylemair         ###   ########.fr       */
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
# include <time.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>

# define _LEN(STR)		ft_strlen(STR)
# define A_LEN(ARRAY)	array_len(ARRAY)
# define P_BASIC(FILE)	ft_putstr(FILE->name)
# define _DIR(NAME) 	ft_putendl(ft_strcat(NAME, ":"));
# define _A(name)		(ft_strcmp(name, ".") && ft_strcmp(name, ".."))
# define OPTION(N)		(N.arg.l||N.arg.br||N.arg.a||N.arg.r||N.arg.t)
# define _OPEN			"ls: impossible d'ouvrir le répertoire \'"
# define _UNKNOW 		"\': No such file or directory"
# define _ACCES 		"\': Permission denied"
# define _LOOP	 		"\': directory causes a cycle\0"
# define _TOOLONG 		"\': Is too long"
# define _NOMEM 		"\': Out of memory"
# define _NOTDIR 		"\': Not a directory"
# define _BAD_FD		"\': Bad file descriptor"
# define _SIXMONTH		(15768000)
# define _PL(X)			ft_putendl(X);
# define PUT(X)			ft_putstr(X);
# define PN(X)			ft_putnbr(X);
# define RED(X) 		ft_putstr("\033[1;31m"); ft_putstr(X);
# define GREEN(X) 		ft_putstr("\033[0;32m"); ft_putstr(X);
# define BLUE(X) 		ft_putstr("\033[0;34m"); ft_putstr(X);
# define CYAN(X) 		ft_putstr("\033[0;36m"); ft_putstr(X);
# define PURPLE(X)		ft_putstr("\033[0;49;35m"); ft_putstr(X);
# define YELLOW(X)		ft_putstr("\033[7;49;33m"); ft_putstr(X);
# define YELLOW_2(X)	ft_putstr("\033[0;49;33m"); ft_putstr(X);
# define RESET() 		ft_putstr("\033[0m");
# define DEL()			ft_strdel(&tmp_path);ft_strdel(&new_path);
# define DIR_NOT_A(S,D)	(S_ISDIR(S)&&ft_strcmp(D, ".")&&ft_strcmp(D, ".."))
# define READ_SUB()		(A_LEN((*meta).err) == (*meta).array_len && new)
# define PATH_MAX		(1024)
# define EXIT_BAD_OPT	(-1)

typedef struct		s_opt
{
	int				l;
	int				br;
	int				a;
	int				r;
	int				t;
}					t_opt;

typedef struct		s_reader
{
	struct stat		sb;
	char			*name;
	char			*path;
	int				sort;
	struct s_reader	*next;
	struct s_reader	*sub;
}					t_reader;

typedef struct		s_ls
{
	t_opt			arg;
	t_reader		*file;
	char			**array;
	char			**err;
	int				error_sd;
	int				array_len;
}					t_ls;

t_reader			*open_directory(t_ls *meta);
t_reader			*read_directory(DIR *space, char *path, t_ls *meta, int i);
t_reader			*create(struct stat	sb, char *name, char *path);
t_reader			*append(t_reader **head, t_reader *last);
int					is_full(t_reader *current);
int					is_next_dir(t_reader *current);
int					get_total(t_reader *current);
int					array_len(char **array);
void				free_array(char **array);
char				**array_add(char **array, char *add);
char				**create_array(char *str);
int					create_or_add(char ***array, char *add, int is_path);
void				free_reader(t_reader *current);
void				free_meta(t_ls *meta);
void				reader(t_ls meta, t_reader *head, t_reader *current,
							int root);
void				reader_sub(t_ls meta, t_reader *current, int root);
void				sort_map(t_reader **file, int (*f)(t_reader *, t_reader *));
void				swap_data(t_reader **a, t_reader **b);
int					cmp_name(t_reader *a, t_reader *b);
int					cmp_time(t_reader *a, t_reader *b);
int					rcmp_name(t_reader *a, t_reader *b);
int					rcmp_time(t_reader *a, t_reader *b);
void				choose_sorting(t_ls *meta);
void				print_basic(t_ls meta, t_reader *current, int root);
void				print_right(mode_t	st_mode);
void				more_print_l(t_reader *current);
void				print_time(t_reader *current);
void				print_l(t_ls meta, t_reader *current);
void				color_name(t_reader *current);
int					get_total(t_reader *current);
char				**stat_error(char **out, char *str, t_ls *meta);
char				**d_error(char **out, char *str, t_ls *meta);
void				output_error(char const **out);
int					strlen_rdelim(const char *str, int c);
int					is_next_dir(t_reader *current);
char				*ft_strndup(const char *str, int len);
t_opt				read_arg(t_opt arg, char c);
t_ls				set_arg(t_ls meta, char **av);
t_ls				init_arg(void);

#endif
