SRC = *.c

OBJ = $(SRC:.c=.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror

NAME = philo

$(NAME):
	$(CC) -pthread -o $(NAME) $(FLAGS) $(addprefix mandatory/, $(SRC)) -g

all: $(NAME)

clean:
	rm -f $(addprefix mandatory/, $(OBJ))

fclean: clean
	rm -f $(NAME)
	
re: fclean all