NAME = cub3D
SRC = cub3D.c init.c map_parse.c raycast.c
OBJ = $(SRC:%.c=%.o)

MODULE = libft/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -L./minilibx -lmlx -lm -lX11 -lXext -g3 -finline-functions -ffast-math -falign-functions -funroll-loops -fstrict-aliasing \
	 -fomit-frame-pointer -flto -Ofast -O1 -O2 -Os -O3

all: $(MODULE) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MODULE) $(LFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(MODULE):
	$(MAKE) -C libft

clean:
	rm -f $(OBJ)
	@$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
