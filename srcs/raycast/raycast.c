/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:52:27 by kenzo             #+#    #+#             */
/*   Updated: 2025/03/18 19:14:40 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	calcul_ray_dir(t_raycast *rc, t_game *game, int x)
{
	rc->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	rc->ray_dir_x = game->player.dir.x + game->player.plane.x * rc->camera_x;
	rc->ray_dir_y = game->player.dir.y + game->player.plane.y * rc->camera_x;
	rc->map_x = (int)game->player.pos.x;
	rc->map_y = (int)game->player.pos.y;
	rc->delta_dist_x = fabs(1 / rc->ray_dir_x);
	rc->delta_dist_y = fabs(1 / rc->ray_dir_y);
}

void	calcul_move_dist(t_raycast *rc, t_game *game)
{
	if (rc->ray_dir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (game->player.pos.x - rc->map_x)
			* rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - game->player.pos.x)
			* rc->delta_dist_x;
	}
	if (rc->ray_dir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (game->player.pos.y - rc->map_y)
			* rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (rc->map_y + 1.0 - game->player.pos.y)
			* rc->delta_dist_y;
	}
}

void	detect_collision(t_raycast *rc, t_game *game)
{
	rc->hit = 0;
	while (rc->hit == 0)
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->map_x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}
		if (game->map->data[rc->map_y][rc->map_x] > 0)
			rc->hit = 1;
	}
}

void	calcul_wall_dist(t_raycast *rc, t_game *game)
{
	if (rc->side == 0)
		rc->perp_wall_dist = (rc->map_x - game->player.pos.x
				+ (1 - rc->step_x) / 2) / rc->ray_dir_x;
	else
		rc->perp_wall_dist = (rc->map_y - game->player.pos.y
				+ (1 - rc->step_y) / 2) / rc->ray_dir_y;
}

void	calcul_textre_x(t_raycast *rc, t_game *game)
{
	if (rc->side == 0)
		rc->wall_x = game->player.pos.y + rc->perp_wall_dist
			* rc->ray_dir_y;
	else
		rc->wall_x = game->player.pos.x + rc->perp_wall_dist
			* rc->ray_dir_x;
	rc->wall_x -= floor(rc->wall_x);
	rc->texture_x = (int)(rc->wall_x * (double)rc->tex_width);
	if (rc->side == 0)
	{
		if (rc->ray_dir_x > 0)
			rc->texture_x = rc->tex_width - rc->texture_x - 1;
	}
	else
	{
		if (rc->ray_dir_y < 0)
			rc->texture_x = rc->tex_width - rc->texture_x - 1;
	}
}
