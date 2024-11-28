NAME = cub3D
SRC = cub3D.c init.c map_parse.c raycast.c
OBJ_DIR = objet
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

MODULE = libft/libfinal.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
LFLAGS = -L./minilibx -lmlx -lm -lX11 -lXext

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
