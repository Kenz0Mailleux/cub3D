/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:14:12 by kenzo             #+#    #+#             */
/*   Updated: 2025/04/22 05:42:16 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

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

int	*allocate_buffer(void)
{
	int	*buffer;

	buffer = (int *)malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(int));
	if (!buffer)
	{
		ft_printf("Erreur malloc");
		return (NULL);
	}
	ft_memset(buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(int));
	return (buffer);
}

void	calculate_ray_for_pixel(t_raycast *rc, t_game *game, int x)
{
	calcul_ray_dir(rc, game, x);
	calcul_move_dist(rc, game);
	detect_collision(rc, game);
	calcul_wall_dist(rc, game);
}

void	calculate_line_height(t_raycast *rc)
{
	rc->line_height = (int)(SCREEN_HEIGHT / rc->perp_wall_dist);
	rc->draw_start = -rc->line_height / 2 + SCREEN_HEIGHT / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = rc->line_height / 2 + SCREEN_HEIGHT / 2;
	if (rc->draw_end >= SCREEN_HEIGHT)
		rc->draw_end = SCREEN_HEIGHT - 1;
}

void	render_ceiling_and_floor(t_raycast *rc, t_game *game, int x)
{
	int	y;

	y = 0;
	while (y < rc->draw_start)
	{
		rc->buffer[y * SCREEN_WIDTH + x] = game->map->ceiling_color;
		y++;
	}
	y = rc->draw_start;
	while (y < rc->draw_end)
	{
		rc->texture_y = ((y - SCREEN_HEIGHT / 2 + rc->line_height / 2)
				* rc->tex_height) / rc->line_height;
		rc->color = *(int *)(rc->texture_data + (rc->texture_y
					* game->images[0].line_length
					+ rc->texture_x * (game->images[0].bpp / 8)));
		rc->buffer[y * SCREEN_WIDTH + x] = rc->color;
		y++;
	}
	y = rc->draw_end;
	while (y < SCREEN_HEIGHT)
	{
		rc->buffer[y * SCREEN_WIDTH + x] = game->map->ground_color;
		y++;
	}
}
