NAME = philo
CC = gcc
FLAGS = -Wall -Wextra -Werror
SRC = $(shell find . -name "*.c")
OBJ = $(SRC:.c=.o)

all:	$(NAME)

$(NAME): $(OBJ) philo.h
			$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
			rm -rf $(OBJ)

fclean: clean
			rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean
