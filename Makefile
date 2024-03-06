# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/15 12:36:59 by fbazaz            #+#    #+#              #
#    Updated: 2024/03/01 15:07:13 by fbazaz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = pipex
NAME_BONUS = pipex_bonus
CFLAGS = -Wall -Wextra -Werror
SRC = ./mandatory/error.c ./mandatory/processes.c ./mandatory/pipex.c
SRC += ./utils/ft_split.c ./utils/ft_strchr.c ./utils/ft_strcmp.c ./utils/ft_strncmp.c ./utils/ft_strdup.c ./utils/ft_strjoin.c ./utils/ft_strlen.c ./utils/ft_putendl_fd.c

SRC_BONUS = ./bonus/execute.c ./bonus/get_next_line.c ./bonus/here_doc.c ./bonus/pipex_bonus.c
SRC_BONUS += ./utils/ft_split.c ./utils/ft_strchr.c ./utils/ft_strcmp.c ./utils/ft_strncmp.c ./utils/ft_strdup.c ./utils/ft_strjoin.c ./utils/ft_strlen.c ./utils/ft_putendl_fd.c

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

bonus: $(NAME_BONUS)

$(NAME_BONUS) : $(OBJ_BONUS)
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJ_BONUS)

clean:
	rm -rf $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -rf $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY : all clean fclean re
