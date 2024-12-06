/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:52:27 by kenzo             #+#    #+#             */
/*   Updated: 2024/12/06 01:58:23 by kenzo            ###   ########.fr       */
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

void	texture_wall(t_raycast *rc, t_game *game)
{
	if (rc->side == 0)
	{
		if (rc->ray_dir_x > 0)
			rc->texture_data = mlx_get_data_addr(game->images[1].img_ptr,
					&game->images[0].bpp, &game->images[0].line_length,
					&game->images[0].endian);
		else
			rc->texture_data = mlx_get_data_addr(game->images[3].img_ptr,
					&game->images[0].bpp, &game->images[0].line_length,
					&game->images[0].endian);
	}
	else
	{
		if (rc->ray_dir_y > 0)
			rc->texture_data = mlx_get_data_addr(game->images[2].img_ptr,
					&game->images[0].bpp, &game->images[0].line_length,
					&game->images[0].endian);
		else
			rc->texture_data = mlx_get_data_addr(game->images[0].img_ptr,
					&game->images[0].bpp, &game->images[0].line_length,
					&game->images[0].endian);
	}
}

void	raycast_calcul(t_game *game)
{
	int			x;
	int			y;
	t_raycast	rc;

	rc.tex_width = 64;
	rc.tex_height = 64;
	rc.buffer = (int *)malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(int));
	if (!rc.buffer)
	{
		perror("Erreur malloc");
		free_all_exit(game, EXIT_FAILURE);
		return ;
	}
	ft_memset(rc.buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(int));
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		calcul_ray_dir(&rc, game, x);
		calcul_move_dist(&rc, game);
		detect_collision(&rc, game);
		calcul_wall_dist(&rc, game);
		rc.line_height = (int)(SCREEN_HEIGHT / rc.perp_wall_dist);
		rc.draw_start = -rc.line_height / 2 + SCREEN_HEIGHT / 2;
		if (rc.draw_start < 0)
			rc.draw_start = 0;
		rc.draw_end = rc.line_height / 2 + SCREEN_HEIGHT / 2;
		if (rc.draw_end >= SCREEN_HEIGHT)
			rc.draw_end = SCREEN_HEIGHT - 1;
		calcul_textre_x(&rc, game);
		texture_wall(&rc, game);
		y = 0;
		while (y < rc.draw_start)
		{
			rc.buffer[y * SCREEN_WIDTH + x] = game->map->ceiling_color;
			y++;
		}
		y = rc.draw_start;
		while (y < rc.draw_end)
		{
			rc.texture_y = ((y - SCREEN_HEIGHT / 2 + rc.line_height / 2)
					* rc.tex_height) / rc.line_height;
			rc.color = *(int *)(rc.texture_data + (rc.texture_y
						* game->images[0].line_length
						+ rc.texture_x * (game->images[0].bpp / 8)));
			rc.buffer[y * SCREEN_WIDTH + x] = rc.color;
			y++;
		}
		y = rc.draw_end;
		while (y < SCREEN_HEIGHT)
		{
			rc.buffer[y * SCREEN_WIDTH + x] = game->map->ground_color;
			y++;
		}
		x++;
	}
	rc.img = mlx_new_image(game->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	rc.data = (int *)mlx_get_data_addr(rc.img, &game->images[0].bpp,
			&game->images[0].line_length, &game->images[0].endian);
	ft_memcpy(rc.data, rc.buffer, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(int));
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, rc.img, 0, 0);
	free(rc.buffer);
	mlx_destroy_image(game->mlx_ptr, rc.img);
}
