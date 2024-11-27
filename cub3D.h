/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:00:08 by kenzo             #+#    #+#             */
/*   Updated: 2024/11/26 19:57:11 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "minilibx/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <string.h>

#define KEY_ESCAPE 53
#define KEY_Z 122
#define KEY_Q 113
#define KEY_S 115
#define KEY_D 100
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MOVE_SPEED 0.1
#define ROT_SPEED 0.05

#define MAP_WIDTH 16 // Vous pouvez adapter cette valeur
#define MAP_HEIGHT 6 // Vous pouvez adapter cette valeur


// Structure pour gérer une image
typedef struct s_image {
    void    *img_ptr;
    char    *path;
} t_image;

typedef struct s_map {
    int **data;
    int width;
    int height;
} t_map;


typedef struct s_vector {
    double x;
    double y;
} t_vector;

typedef struct s_player
{
    t_vector pos;       // Position (x, y)
    t_vector dir;       // Direction (vecteur)
    t_vector plane;     // Plan caméra
} t_player;

// Structure principale pour MLX
typedef struct s_game
{
    void    *mlx_ptr;
    void    *win_ptr;
    t_image images[4];  // Un tableau pour stocker les textures

    t_player player;   // Structure contenant les informations du joueur

    int     map_width;
    int     map_height;
    t_map   *map;      // La carte du jeu

    // Membres nécessaires au raycasting
    double  ray_dir_x;
    double  ray_dir_y;
    double  delta_dist_x;
    double  delta_dist_y;
    double  side_dist_x;
    double  side_dist_y;
    int     step_x;
    int     step_y;
    int     side;
    double  perp_wall_dist;

    int     **zbuffer;  // Optionnel : utilisé pour le calcul de la profondeur de champ

} t_game;

t_game *init_game(int width, int height, char *title);
void test_images(t_game *mlx, int width, int height);
void draw_scene(t_game *game);
void perform_raycasting(t_game *game);
int handle_keypress(int keycode, t_game *game);

#endif