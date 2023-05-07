# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/18 10:32:25 by mparisse          #+#    #+#              #
#    Updated: 2023/05/07 03:56:47 by mparisse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = main.c utils.c parser.c init.c mini_lib.c mini_lib_2.c routine.c


OBJS = ${SRCS:.c=.o}

CC = cc -g3

CFLAGS = -Wall -Werror -Wextra

# LIBS = libft/libft.a 

all : $(NAME)

# YELLOW = \033[0;93m
# @echo "Compiling libft"
# @make --no-print-directory -C libft 
# @echo "Bien joue!"

$(NAME) : ${OBJS}
# make -C libft
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

.c.o :
	${CC} -Wall -Werror -Wextra -c $< -o ${<:.c=.o}

norme :
	norminette $(SRCS) libft

clean : 
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean $(NAME)

.PHONY : all clean fclean re libft mlx_linux
#.SILENT : all clean fclean re $(OBJS)
