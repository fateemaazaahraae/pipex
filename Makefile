# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/15 12:36:59 by fbazaz            #+#    #+#              #
#    Updated: 2024/02/28 10:17:19 by fbazaz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CFILE = mandatory/pipex.c\
		mandatory/error.c\
		mandatory/processes.c\
		libft/libft.a

CBONUS = bonus/execute.c\
		 bonus/pipex_bonus.c\
		 bonus/here_doc.c\
		 bonus/get_next_line.c\
		 libft/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address

all : $(NAME)

$(NAME) :
		make -C libft
		$(CC) $(CFLAGS) $(CFILE) -o $(NAME)

clean :
	make clean -C libft
	rm -rf $(NAME)

fclean : clean
	make fclean -C libft
	rm -rf $(NAME)

bonus : fclean
		make all -C libft
		$(CC) $(CFLAGS) $(CBONUS) -o $(NAME)

re : fclean all

.PHONY : all clean fclean re
