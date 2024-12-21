NAME = philo

SRC =	main.c \
		parcing.c \
		init.c \
		dinner.c \
		monitor.c \
		routine.c \
		utils.c \
		clear.c

OBJ = $(SRC:.c=.o)

CFLAG = -Wall -Wextra -Werror # -fsanitize=address -g3

CC = cc

INCLUDE = philo.h

%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@

$(NAME) : $(OBJ) $(INCLUDE)	
	$(CC) $(CFLAG) $(OBJ) -o $(NAME)

all : $(NAME)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re

.SECONDARY : $(OBJ)
