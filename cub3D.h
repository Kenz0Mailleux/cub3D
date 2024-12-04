/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:00:08 by kenzo             #+#    #+#             */
/*   Updated: 2024/12/04 18:57:40 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "minilibx/mlx.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define KEY_ESCAPE 65307
#define KEY_Z 122
#define KEY_Q 113
#define KEY_S 115
#define KEY_D 100
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MOVE_SPEED 0.1
#define ROT_SPEED 0.05

#define MAP_WIDTH 16
#define MAP_HEIGHT 6


// typedef struct s_dico
// {
// 	char *key;
// 	char *value;
// } t_dico;

// Structure pour gérer une image
typedef struct s_image
{
    void    *img_ptr;
    char    *path;
	int		found;
    int     *data;
    int     bpp;
    int     line_length;
    int     endian;
} t_image;

typedef struct s_map
{
    int 	**data;
    int 	width;
    int 	height;
	t_image	image[6];
} t_map;

typedef struct s_vector
{
    double x;
    double y;
} t_vector;

typedef struct s_player
{
    t_vector	pos;
    t_vector	dir;
    t_vector	plane;
	int			initialised;
} t_player;


typedef struct s_raycast
{
    double camera_x;
    double ray_dir_x;
    double ray_dir_y;
    int map_x;
    int map_y;
    double delta_dist_x;
    double delta_dist_y;
    double side_dist_x;
    double side_dist_y;
    int step_x;
    int step_y;
    int hit;
    int side;
    double perp_wall_dist;
    int line_height;
    int draw_start;
    int draw_end;
    int texture_x;
    int texture_y;
    double wall_x;
    int tex_width;
	int tex_height;    
    char *texture_data;
    int color;
    int *buffer;
    void *img;
    int *data;
} t_raycast;

typedef struct s_game
{
    void    *mlx_ptr;
    void    *win_ptr;
    t_image images[6];
	int		bpp;
    t_player player;
    int     map_width;
    int     map_height;
    t_map   *map;
} t_game;

void print_map(t_map *map);
void test_images(t_game *mlx, int width, int height);
void draw_scene(t_game *game);
void raycast_calcul(t_game *game);
int handle_keypress(int keycode, t_game *game);
t_map *parse_map(char *filename, t_game *game);
void	load_images(t_game *game, int width, int height, int floor_color, int ceiling_color);
t_game *init_game(char *path, int width, int height, char *title);
void free_map(int **map, int height);
void free_all_exit(t_game *game, int succes);
void calculate_wall_distance(t_game *game, t_raycast *rc);
void render_wall_slice(t_game *game, t_raycast *rc, int *buffer, int x);
void render_to_window(t_game *game, int *buffer);


#endif
