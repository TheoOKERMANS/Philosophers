LIBFT = -L libft/ -lft

SRC = pipex.c err.c cmd.c path.c free.c

OBJ = $(SRC:.c=.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror

NAME = philo

$(NAME):
	make -C ./libft
	$(CC) -o $(NAME) $(FLAGS) $(addprefix mandatory/, $(SRC)) $(LIBFT) -g

all: $(NAME)

clean:
	rm -f $(addprefix mandatory/, $(OBJ))
	make clean -C ./libft

fclean: clean
	rm -f $(NAME)
	make fclean -C ./libft
	
re: fclean all