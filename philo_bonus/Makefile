# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 19:15:41 by aeid              #+#    #+#              #
#    Updated: 2024/05/22 18:10:56 by aeid             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
CC = cc -g -pthread
RM = rm -f
CFLAGS = -Wall -Werror -Wextra

HEADER = philo_bonus.h

B_SRC = main_bonus.c checks_bonus.c dinner_bonus.c utils_bonus.c sem_handling_bonus.c utils1_bonus.c monitor_bonus.c free_bonus.c
B_OBJ = $(B_SRC:.c=.o)

%.o: %.c $(HEADER) Makefile
	@$(CC) $(CFLAGS) -c $< -o $@
	
$(NAME): $(B_OBJ)
	@$(CC) $(B_OBJ) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(B_OBJ)
	
fclean: clean
	$(RM) $(NAME)

sem:
	$(RM) /dev/shm/sem.block_fork
	$(RM) /dev/shm/sem.block_write
	$(RM) /dev/shm/sem.block_control
	$(RM) /dev/shm/sem.block_end
	
re: fclean all
.PHONY: all clean fclean re