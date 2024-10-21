NAME = philo
CC = cc
FLAGS = -Wall -Wextra -Werror -pthread
#-fsanitize=thread

SRC = src/main.c src/initialize.c src/utils_philo.c  src/error_memory.c src/utils_libft.c \
	src/routine.c src/monitor.c
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