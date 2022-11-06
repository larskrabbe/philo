# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 00:02:46 by lkrabbe           #+#    #+#              #
#    Updated: 2022/11/06 21:06:58 by lkrabbe          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH = src

NAME = philo

CC = cc -pthread

CFLAGS =  -Wextra -Wall  -g -fsanitize=thread #-fsanitize=addres -Werror

DIR_SRC = src

DIR_OBJ = obj

SRC = main.c \
		statechange.c \
		parsing.c\
		createphilosophers.c\
		statecycle.c\
		get_next_arg.c\

OBJ = $(SRC:.c=.o) $(DIR_LIBFT_PLUS:.c=.o) 

all :  $(OBJ)
	@echo	"\033[0;32m compiling $(NAME)\n\033[0m"
	$(CC) -g -fsanitize=thread $(OBJ) -o $(NAME)
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

ARGS = "1 2 2"
test:
		cc src/get_next_arg.c -o get_next_arg.out 
		@echo 
		./get_next_arg.out hallo "  " world "  this is a test"
		@echo
re : fclean all

.phony: all re clean fclean 