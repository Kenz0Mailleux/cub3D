NAME = cub3D
SRC = srcs/cub3D.c srcs/init.c srcs/utils.c srcs/handler.c srcs/free_memory.c\
	srcs/map_parse/file_parse.c srcs/map_parse/map_parse.c srcs/map_parse/map_parse2.c srcs/map_parse/map_parse3.c srcs/map_parse/map_parse4.c \
	srcs/map_parse/map_memory.c srcs/map_parse/parse_color.c srcs/map_parse/map_algo.c\
	srcs/raycast/raycast.c srcs/raycast/raycast2.c srcs/raycast/raycast3.c


OBJ = $(SRC:%.c=%.o)

MODULE = libft/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g 
LFLAGS = -L./minilibx -lmlx -lm -lX11 -lXext -g3 \
	-finline-functions -ffast-math -falign-functions -funroll-loops -fstrict-aliasing \
	-fomit-frame-pointer -flto -Ofast -O1 -O2 -Os -O3

all: $(MODULE) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MODULE)  $(LFLAGS) -o $(NAME)

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
