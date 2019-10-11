/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 15:24:04 by cylemair          #+#    #+#             */
/*   Updated: 2019/10/11 19:41:31 by cylemair         ###   ########.fr       */
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
# include <errno.h>

# define _LEN(STR)		ft_strlen(STR)
# define A_LEN(ARRAY)	array_len(ARRAY)
# define IS_DIR(F, D)	(S_ISDIR(F.st_mode) 			\
						&& ft_strcmp(D->d_name, ".")	\
						&& ft_strcmp(D->d_name, ".."))
# define P_BASIC(FILE)	ft_putstr(FILE->name)
# define _DIR(NAME) 	ft_putendl(ft_strcat(NAME, ":"));
# define _A(name)		(ft_strcmp(name, ".")		\
						&& ft_strcmp(name, ".."))

# define BAD_OPTION(N)	(N.arg._l || N.arg._R || N.arg._a \
						|| N.arg._r || N.arg._t)

# define _OPEN			"ls: impossible d'ouvrir le répertoire \'"

# define _UNKNOW 		"\': No such file or directory"
# define _ACCES 		"\': Permission denied"
# define _LOOP	 		"\': Too many symbolic links"
# define _TOOLONG 		"\': Is too long"
# define _NOMEM 		"\': Out of memory"

# define _SIXMONTH		(15768000)

# define _PL(X)			ft_putendl(X);
# define PUT(X)			ft_putstr(X);
# define PN(X)			ft_putnbr(X);
# define RED(X) 		ft_putstr("\033[1;31m"); 		\
						ft_putstr(X);
# define GREEN(X) 		ft_putstr("\033[0;32m"); 		\
						ft_putstr(X);
# define BLUE(X) 		ft_putstr("\033[0;34m"); 		\
						ft_putstr(X);
# define CYAN(X) 		ft_putstr("\033[0;36m"); 		\
						ft_putstr(X);
# define RESET() 		ft_putstr("\033[0m")
# define PR(NAME, E)	ft_putstr("\033[1;31m");		\
						ft_putstr_fd("ls: ", 2);		\
						ft_putstr_fd(NAME, 2);			\
						ft_putstr_fd(": ", 2);			\
						ft_putstr_fd(E, 2);				\
						ft_putstr_fd("\n", 2);			\
						RESET();						\
						exit(-1);						\

# define ABUSE()		if (ft_strncmp(dir->d_name,		\
						".", 1) || (*meta).arg._a)		\
						len = ft_strjoin(path,		\
						((tmp_path = ft_strjoin("/",	\
						dir->d_name))));			 	\
						if (len && lstat(len,	\
						&sb))							\
						(*meta)._err =					\
						stat_error((*meta)._err,		\
						(*meta).array, i, len);			\
# define VAR()			t_reader		*tmp;			\
						t_reader		*head;			\
						DIR				*sub;			\
						struct dirent	*dir;			\
						struct stat		sb;				\
						char			*len;			\
						char			*tmp_path;		\
# define DISPLAY()		print_right(current->sb.st_mode);	\
						ft_putchar(' ');					\
						ft_putnbr(current->sb.st_nlink);	\
						ft_putchar(' ');					\
						ft_putstr((getpwuid(current->sb.st_uid))->pw_name);	\
						ft_putchar(' ');					\
						ft_putstr((getgrgid(current->sb.st_gid))->gr_name);	\
						ft_putchar(' ');					\
						ft_putnbr(current->sb.st_size);		\
						ft_putchar('\t');					\

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
	char			**_err;
	int				array_len;
}					t_ls;

t_reader	*open_directory(t_ls *meta);
t_reader	*read_directory(DIR *directory, char *path, t_ls *meta, int i);
t_reader    *create(struct stat	sb, char *name, char *path);
t_reader    *append(t_reader **head, t_reader *last);
int			is_full(t_reader *current);
int			is_next_dir(t_reader *current);
int			get_total(t_reader *current);

int			array_len(char **array);
void		free_array(char **array);
char		**create_array(char *str);
char		**array_add(char** array, char *add);
int			create_or_add(char ***array, char *add);
void		free_reader(t_reader *current);
void		free_meta(t_ls *meta);

void		reader(t_ls meta, t_reader *head, t_reader *current, int root);
void		reader_sub(t_ls meta, t_reader *current, int root);

void		sort_map(t_reader **file, int (*f)(t_reader *, t_reader *));
void		swap_data(t_reader **a, t_reader **b);
int			cmp_name(t_reader *a, t_reader *b);
int			cmp_time(t_reader *a, t_reader *b);
int			rcmp_name(t_reader *a, t_reader *b);
int			rcmp_time(t_reader *a, t_reader *b);
void		choose_sorting(t_ls *meta);

void		print_basic(t_ls meta, t_reader *current, int root);
void		print_right(mode_t	st_mode);
void 		print_l(t_ls meta, t_reader *current);
int			get_total(t_reader *current);

char		**stat_error(char **out, char**array, int index, char *str);
char		**d_error(char **out, char **array, int index, char *str);
void		output_error(char const **out);

int			strlen_rdelim(const char *str, int c);
int			is_next_dir(t_reader *current);
char		*ft_strndup(const char *str, int len);

t_opt		read_arg(t_opt arg, char c);
t_ls		set_arg(t_ls meta, char **av);
t_ls		init_arg(void);

#endif
