NAME = cub3D
SRC = cub3D.c init.c map_parse.c raycast.c
OBJ = $(SRC:%.c=%.o)

MODULE = libft/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -L./minilibx -lmlx -lm -lX11 -lXext -g3 -finline-functions -ffast-math -falign-functions -funroll-loops -fstrict-aliasing \
	 -fomit-frame-pointer -flto -Ofast -O1 -O2 -Os -O3 

# Règle principale pour construire l'exécutable
all: $(MODULE) $(NAME)

# Lier les fichiers objets et la bibliothèque libft pour créer l'exécutable
$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MODULE) $(LFLAGS) -o $(NAME)

# Compilation des fichiers source en fichiers objets dans le répertoire courant
%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Règle pour générer libft.a
$(MODULE):
	$(MAKE) -C libft

# Nettoyage des fichiers objets et exécutables
clean:
	rm -f $(OBJ)
	@$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C libft fclean

# Reconstruction complète
re: fclean all

# Pour gérer les dépendances
-include $(OBJ:.o=.d)

.PHONY: all clean fclean re
