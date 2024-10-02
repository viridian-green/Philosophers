NAME = philo
CC = cc
FLAGS = -Wall -Wextra -Werror -pthread
#-fsanitize=thread

SRC = main.c initialize.c utils_philo.c  error_memory.c utils_libft.c

OBJ = $(SRC:.c=.o)

all = $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

flcean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re