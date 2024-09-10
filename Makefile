# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/11 15:19:11 by sklaps            #+#    #+#              #
#    Updated: 2024/09/10 14:32:09 by sklaps           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			philo
FILES = 		philo.c \
				time.c \
				ft_atoi.c \
				close.c \
				len.c
SRC_DIR =		src/
SRC =			$(addprefix $(SRC_DIR), $(FILES))
OBJ =			${SRC:.c=.o}
CC = 			cc
CFLAGS =		-Wall -Wextra -Werror -g -pthread
RM =			rm -rf

all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean :
	${RM} $(OBJ)

fclean : clean
	${RM} $(NAME)

re : fclean all

.PHONY: all clean fclean re
