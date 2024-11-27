NAME = cub3D
SRC = cub3D.c
OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall #-Wextra -Werror
LFLAGS = -L./minilibx -lmlx -lm -lX11 -lXext

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all