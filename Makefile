# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/11 15:19:11 by sklaps            #+#    #+#              #
#    Updated: 2024/09/08 15:44:17 by sklaps           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			philo
FILES = 		philo.c \
				time.c \
				ft_atoi.c
SRC_DIR =		src/
SRC =			$(addprefix $(SRC_DIR), $(FILES))
OBJ =			${SRC:.c=.o}
CC = 			cc
CFLAGS =		-Wall -Wextra -Werror -g
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
