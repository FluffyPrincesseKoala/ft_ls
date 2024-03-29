# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/01 15:17:18 by cylemair          #+#    #+#              #
#    Updated: 2019/10/18 15:28:48 by cylemair         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=		gcc -g3 #-fsanitize=address

LDFLAGS	=		-L libft/ -lft -I includes/

CFLAGS	+=		-Werror -Wall -Wextra

NAME	=		ft_ls

RM		=		rm -rf

SRC		=		srcs/main.c 			\
				srcs/array.c			\
				srcs/lst_function.c 	\
				srcs/print.c 			\
				srcs/print_l.c 			\
				srcs/sorting.c 			\
				srcs/sorting_method.c 	\
				srcs/error.c 			\
				srcs/free.c 			\
				srcs/string.c 			\
				srcs/directory.c		\
				srcs/init.c				\
				srcs/reader.c			\

DIR		=		includes/

OBJS	=		$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft/
	$(CC)  -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	make clean -C libft/
	$(RM) $(OBJS)

fclean: clean
	make fclean -C libft/
	$(RM) $(NAME)

re: fclean all

PHONY: all clean fclean re
