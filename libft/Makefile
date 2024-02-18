# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/21 15:04:18 by fbazaz            #+#    #+#              #
#    Updated: 2024/02/18 09:29:15 by fbazaz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFILE = ft_strlen.c ft_strncmp.c ft_strdup.c ft_strjoin.c ft_split.c 
OFILE = $(CFILE:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OFILE)
		  ar rc $(NAME) $(OFILE)

clean :
	rm -f $(OFILE)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
