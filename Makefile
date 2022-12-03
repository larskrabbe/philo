# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 00:02:46 by lkrabbe           #+#    #+#              #
#    Updated: 2022/12/03 13:35:05 by lkrabbe          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH = src

NAME = philo

CC = cc -pthread

CFLAGS = -Wextra -Wall -Werror  #-g -fsanitize=thread #-fsanitize=addres 

DIR_SRC = src

DIR_OBJ = obj

SRC = main.c \
		statechange.c \
		parsing.c\
		statecycle.c\
		get_next_arg.c\
		waiter.c\
		waiter_setup.c\
		philo_setup.c\
		time_utils.c\
		utils.c


# OBJ=$(addprefix $(OBJ_DIR),$(OBJ_NAME))

# SRC=$(addprefix $(SRC_DIR),$(SRC_NAME))

OBJ=$(SRC:.c=.o)
all :  $(OBJ)
	@echo	"\033[0;32m compiling $(NAME)\n\033[0m"
	$(CC) $(OBJ) -o $(NAME)
	@echo	"\033[0;32m compiling finished\n\033[0m"

run:all
	./$(NAME)

%.o: %.c $(DIR_OBJ)
	$(CC) -c $(CFLAGS) $< -o  $@


$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

clean :
		@echo	"\033[1;31m"
		rm -f *.o
		@echo	"\033[0;0m"

fclean : clean 
		@echo	"\033[1;31m"
		rm -f $(NAME)
		@echo	"\033[0;0m"

re : fclean all

.phony: all re clean fclean 