# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 19:15:41 by aeid              #+#    #+#              #
#    Updated: 2024/05/22 18:11:47 by aeid             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc -g -pthread
RM = rm -f
CFLAGS = -Wall -Werror -Wextra

HEADER = philo.h

M_SRC = main.c checks.c initialise.c dinner.c utils.c utils_checks.c big_brother.c utils1.c
M_OBJ = $(M_SRC:.c=.o)

%.o: %.c $(HEADER) Makefile
	@$(CC) $(CFLAGS) -c $< -o $@
	
$(NAME): $(M_OBJ)
	@$(CC) $(M_OBJ) -o $(NAME)
	
all: $(NAME)

clean:
	$(RM) $(M_OBJ)
	
fclean: clean
	$(RM) $(NAME)

re: fclean all
.PHONY: all clean fclean re