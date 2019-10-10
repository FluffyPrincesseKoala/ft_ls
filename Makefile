# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/01 15:17:18 by cylemair          #+#    #+#              #
#    Updated: 2019/10/11 00:26:07 by cylemair         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=		gcc -g3 #-fsanitize=address

LDFLAGS	+=		-Llibft -Werror -Wall -Wextra

CFLAGS	+=		-Iincludes -Ilibft

NAME	=		ft_ls

RM		=		rm -rf

SRC		=		srcs/main.c 			\
				srcs/array.c			\
				srcs/lst_function.c 	\
				srcs/print.c 			\
				srcs/sorting.c 			\
				srcs/sorting_method.c 	\
				srcs/error.c 			\
				srcs/free.c 			\

LIBA	=		libft/libft.a

DIR		=		includes/

OBJS	:=		$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -o $(NAME) $(OBJS) $(LIBA)

$(LIBFT):
	make re -C libft/

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

PHONY: all clean fclean re
