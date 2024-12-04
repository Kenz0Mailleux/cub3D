/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:00:41 by kenzo             #+#    #+#             */
/*   Updated: 2024/11/26 19:58:33 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "cub3D.h"

int ft_strlen(const char *s)
{
	int len = 0;

	while (s[len] != '\0')
	{
		len++;
	}

	return len;
}


void ft_putstr_fd(const char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

// Fonction pour allouer la carte
int **allocate_map(int width, int height) {
    int **map;
    int i;

    map = (int **)malloc(sizeof(int *) * height);
    if (!map) {
        perror("Erreur d'allocation de la carte");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < height; i++) {
        map[i] = (int *)malloc(sizeof(int) * width);
        if (!map[i]) {
            perror("Erreur d'allocation d'une ligne de la carte");
            exit(EXIT_FAILURE);
        }
    }

    return map;
}

// Fonction pour libérer la carte
void free_map(int **map, int height) {
    for (int i = 0; i < height; i++) {
        free(map[i]);
    }
    free(map);
}

// fct chatgpt en attendant de faire la mienne
t_map *parse_map(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    t_map *map = malloc(sizeof(t_map));
    if (!map) {
        perror("Erreur d'allocation de la structure de carte");
        exit(EXIT_FAILURE);
    }

    char line[1024];
    int width = 0, height = 0;

    // Lire les lignes du fichier pour déterminer la taille de la carte
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '1' || line[0] == '0') {  // Trouver la première ligne de la carte
            int len = strlen(line);
            if (len > width) width = len; // Calculer la largeur maximale de la carte
            height++;
        }
    }

    // Rewind pour relire le fichier depuis le début
    rewind(file);

    // Allouer la carte avec la taille calculée
    map->data = allocate_map(width, height);
    map->width = width;
    map->height = height;

    // Lire à nouveau le fichier et remplir la carte
    int y = 0;
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '1' || line[0] == '0') {  // Ligne de la carte
            for (int x = 0; x < width; x++) {
                if (line[x] == '1') {
                    map->data[y][x] = 1;  // Mur
                } else if (line[x] == '0') {
                    map->data[y][x] = 0;  // Espace vide
                } else {
                    map->data[y][x] = 0;  // Par défaut espace vide
                }
            }
            y++;
        }
    }

    fclose(file);
    return map;
}

// Fonction pour afficher la carte dans la console
void print_map(t_map *map)
{
	int y;
	int x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			printf("%d ", map->data[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}


void free_all_exit(t_game *game)
{
	int i;

	i = 0;
	if (game)
	{
		if (game->mlx_ptr)
		{
			while (i < 4)
			{
				if (game->images[i].img_ptr)
					mlx_destroy_image(game->mlx_ptr, game->images[i].img_ptr);
				i++;
			}
			if (game->win_ptr)
				mlx_destroy_window(game->mlx_ptr, game->win_ptr);
			mlx_destroy_display(game->mlx_ptr);
			free(game->mlx_ptr);
		}
		free_map(game->map->data, game->map->height);
		free(game->map);
		free(game);
	}
	exit(EXIT_FAILURE);
}

void init_image_paths(t_game *game)
{
	game->images[0].path = "image/north.xpm";
	game->images[1].path = "image/east.xpm";
	game->images[2].path = "image/south.xpm";
	game->images[3].path = "image/west.xpm";
}

// Fonction pour charger les images
void load_images(t_game *game, int width, int height)
{
	game->images[0].img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, game->images[0].path, &width, &height);
	if (!game->images[0].img_ptr)
		free_all_exit(game);
	game->images[1].img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, game->images[1].path, &width, &height);
	if (!game->images[1].img_ptr)
		free_all_exit(game);
	game->images[2].img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, game->images[2].path, &width, &height);
	if (!game->images[2].img_ptr)
		free_all_exit(game);
	game->images[3].img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, game->images[3].path, &width, &height);
	if (!game->images[3].img_ptr)
		free_all_exit(game);
}

t_game *init_game(int width, int height, char *title)
{
	t_game *game;

	game = malloc(sizeof(t_game));
	if (!game)
		free_all_exit(game);
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		free_all_exit(game);
	game->win_ptr = mlx_new_window(game->mlx_ptr, width, height, title);
	if (!game->win_ptr)
		free_all_exit(game);
	init_image_paths(game);
	load_images(game, width, height);
	return (game);
}

void draw_scene(t_game *game)
{
	int x;
	int y;

	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	// Plafond et sol
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			if (y < SCREEN_HEIGHT / 1.5)
				mlx_pixel_put(game->mlx_ptr, game->win_ptr, x, y, 0x87CEEB); // plafond
			else
				mlx_pixel_put(game->mlx_ptr, game->win_ptr, x, y, 0x00FF7F); // Sol
			x++;
		}
		y++;
	}

	// raycasting
	// perform_raycasting(game);
}


int handle_keypress(int keycode, t_game *game)
{
	double old_dir_x;

	printf("Keycode reçu : %d\n", keycode);
	if (keycode == KEY_ESCAPE)
		free_all_exit(game);
	if (keycode == KEY_Z) //forward
	{
		if (game->map->data[(int)(game->player.pos.y)][(int)(game->player.pos.x + game->player.dir.x * MOVE_SPEED)] == 0)
			game->player.pos.x += game->player.dir.x * MOVE_SPEED;
		if (game->map->data[(int)(game->player.pos.y + game->player.dir.y * MOVE_SPEED)][(int)game->player.pos.x] == 0)
			game->player.pos.y += game->player.dir.y * MOVE_SPEED; 
	}
	if (keycode == KEY_S) //back
	{
		if (game->map->data[(int)(game->player.pos.y)][(int)(game->player.pos.x - game->player.dir.x * MOVE_SPEED)] == 0)
			game->player.pos.x -= game->player.dir.x * MOVE_SPEED;
		if (game->map->data[(int)(game->player.pos.y - game->player.dir.y * MOVE_SPEED)][(int)game->player.pos.x] == 0)
			game->player.pos.y -= game->player.dir.y * MOVE_SPEED;
	}
	if (keycode == KEY_Q) //left
	{
		old_dir_x = game->player.dir.x;
		game->player.dir.x = game->player.dir.x * cos(-ROT_SPEED) - game->player.dir.y * sin(-ROT_SPEED);
		game->player.dir.y = old_dir_x * sin(-ROT_SPEED) + game->player.dir.y * cos(-ROT_SPEED);
	}
	if (keycode == KEY_D) //right
	{
		old_dir_x = game->player.dir.x;
		game->player.dir.x = game->player.dir.x * cos(ROT_SPEED) - game->player.dir.y * sin(ROT_SPEED);
		game->player.dir.y = old_dir_x * sin(ROT_SPEED) + game->player.dir.y * cos(ROT_SPEED);
	}
	return (0);
}

int close_game(t_game *game)
{
    mlx_destroy_window(game->mlx_ptr, game->win_ptr);
    free_all_exit(game);
    exit(0);
    return (0);
}


void start_loop(t_game *game)
{
	draw_scene(game);
	mlx_hook(game->win_ptr, 2, 1L << 0, handle_keypress, game);
	//mlx_hook(game->win_ptr, 3, 1L << 1, handle_keyrelease, game);
	mlx_hook(game->win_ptr, 17, 0, close_game, game);
	mlx_loop(game->mlx_ptr);
}

int main(void)
{
	t_game *game;

	game = init_game(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	// game->player.pos.x = 2.5; // Position initiale
	// game->player.pos.y = 2.5;
	// game->player.dir.x = -1; // Direction initiale
	// game->player.dir.y = 0;
	// game->player.plane.x = 0;
	// game->player.plane.y = 0.66;
	// game->map = parse_map("map.cub");
	//print_map(game->map);

	start_loop(game);
	return 0;
}

