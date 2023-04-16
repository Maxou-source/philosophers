# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/18 10:32:25 by mparisse          #+#    #+#              #
#    Updated: 2023/04/14 20:59:23 by mparisse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = main.c


OBJS = ${SRCS:.c=.o}

CC = cc 

CFLAGS = -Wall -Werror -Wextra

LIBS = libft/libft.a 

all : $(NAME)

# YELLOW = \033[0;93m
# @echo "Compiling libft"
# @make --no-print-directory -C libft 
# @echo "Bien joue!"

$(NAME) : ${OBJS}
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

.c.o :
	${CC} -Wall -Werror -Wextra -c $< -o ${<:.c=.o}

norme :
	norminette $(SRCS) libft

clean : 
	make -C libft/ clean
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)
	make -C libft/ fclean

re : fclean $(NAME)

.PHONY : all clean fclean re libft mlx_linux
#.SILENT : all clean fclean re $(OBJS)
