SRC = free.c \
main.c \
math.c \
philo.c \
tid.c \
utils.c \
init.c \
philoeat.c \
fork.c

OBJ = $(SRC:.c=.o)
CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = philo

$(NAME):
	$(CC) -pthread -c $(addprefix mandatory/, $(SRC)) $(FLAGS)
	$(CC) -o $(NAME) $(FLAGS) $(OBJ) -g
	mkdir obj
	mv $(OBJ) obj

all: $(NAME)

clean:
	rm -f $(addprefix mandatory/, $(OBJ))
	rm -rf obj

fclean: clean
	rm -f $(NAME)
	
re: fclean all