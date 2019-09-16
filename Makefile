# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: princesse <princesse@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/01 15:17:18 by cylemair          #+#    #+#              #
#    Updated: 2019/09/10 16:46:30 by princesse        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=		gcc -g3

LDFLAGS	+=		-Llibft -Werror -Wall -Wextra

CFLAGS	+=		-Iincludes -Ilibft

NAME	=		ft_ls

RM		=		rm -rf

SRC		=		srcs/main.c 		\
				srcs/array.c		\
				srcs/lst_function.c \

LIBFT	=		libft/libft.a

DIR		=		includes/

OBJS	:=		$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS) $(LIBFT)

$(LIBFT):
	make -C libft/

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

PHONY: all clean fclean re