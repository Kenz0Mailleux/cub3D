/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:48:01 by kenzo             #+#    #+#             */
/*   Updated: 2024/11/26 19:40:31 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void		calculate_step_and_side_dist(t_game *game, double ray_dir_x, double ray_dir_y, 
					int *step_x, int *step_y, double *side_dist_x, double *side_dist_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)game->player.pos.x;
	map_y = (int)game->player.pos.y;

	if (ray_dir_x < 0)
	{
		*step_x = -1;
		*side_dist_x = (game->player.pos.x - map_x) * (1 / ray_dir_x);
	}
	else
	{
		*step_x = 1;
		*side_dist_x = (map_x + 1.0 - game->player.pos.x) * (1 / ray_dir_x);
	}

	if (ray_dir_y < 0)
	{
		*step_y = -1;
		*side_dist_y = (game->player.pos.y - map_y) * (1 / ray_dir_y);
	}
	else
	{
		*step_y = 1;
		*side_dist_y = (map_y + 1.0 - game->player.pos.y) * (1 / ray_dir_y);
	}
}

static int	perform_dda(t_game *game, double ray_dir_x, double ray_dir_y, int step_x, int step_y)
{
	int		map_x;
	int		map_y;
	int		hit;
	int		side;

	map_x = (int)game->player.pos.x;
	map_y = (int)game->player.pos.y;
	hit = 0;

	while (!hit)
	{
		if (game->side_dist_x < game->side_dist_y)
		{
			game->side_dist_x += game->delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			game->side_dist_y += game->delta_dist_y;
			map_y += step_y;
			side = 1;
		}

		if (map_x < 0 || map_x >= game->map_width || map_y < 0 || map_y >= game->map_height)
		{
			return (-1); // Rayon hors limite
		}
		if (game->map->data[map_y][map_x] > 0)
    		hit = 1;
	}
	return (side);
}

static void		calculate_wall_distance(t_game *game, double ray_dir_x, double ray_dir_y, int side)
{
	if (side == 0)
		game->perp_wall_dist = (game->player.pos.x - game->player.pos.x + (1 - game->step_x) / 2) / ray_dir_x;
	else
		game->perp_wall_dist = (game->player.pos.y - game->player.pos.y + (1 - game->step_y) / 2) / ray_dir_y;
}

static void		draw_wall_slice(t_game *game, int x, int draw_start, int draw_end)
{
	t_image		*texture;
	int			y;

	if (game->side == 0)
		texture = (game->ray_dir_x > 0) ? &game->images[1] : &game->images[3];
	else
		texture = (game->ray_dir_y > 0) ? &game->images[2] : &game->images[0];

	if (texture && texture->img_ptr)
	{
		for (y = draw_start; y < draw_end; y++)
			mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, texture->img_ptr, x, y);
	}
	else
	{
		ft_putstr_fd("Erreur de texture\n", 2);
	}
}

void		perform_raycasting(t_game *game)
{
	int		x;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		draw_start;
	int		draw_end;
	int		line_height;
	int		side;

	for (x = 0; x < 800; x++) // Largeur de la fenêtre
	{

		camera_x = 2 * x / (double)800 - 1; // Coordonnée de la caméra
		ray_dir_x = game->player.dir.x + game->player.plane.x * camera_x;
		ray_dir_y = game->player.dir.y + game->player.plane.y * camera_x;

		game->delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
		game->delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);

		calculate_step_and_side_dist(game, ray_dir_x, ray_dir_y, &game->step_x, &game->step_y, 
					&game->side_dist_x, &game->side_dist_y);

		side = perform_dda(game, ray_dir_x, ray_dir_y, game->step_x, game->step_y);
		if (side == -1)
			continue;

		calculate_wall_distance(game, ray_dir_x, ray_dir_y, side);

		line_height = (int)(600 / game->perp_wall_dist);
		draw_start = -line_height / 2 + 300;
		draw_end = line_height / 2 + 300;
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= 600)
			draw_end = 599;

		draw_wall_slice(game, x, draw_start, draw_end);
	}
}
