/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:14:10 by kenzo             #+#    #+#             */
/*   Updated: 2025/04/27 22:27:10 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	display_image(t_game *game, t_raycast *rc)
{
	rc->img = mlx_new_image(game->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	rc->data = (int *)mlx_get_data_addr(rc->img, &game->images[0].bpp,
			&game->images[0].line_length, &game->images[0].endian);
	ft_memcpy(rc->data, rc->buffer, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(int));
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, rc->img, 0, 0);
	free(rc->buffer);
	mlx_destroy_image(game->mlx_ptr, rc->img);
}

void	raycast_calcul(t_game *game)
{
	int			x;
	t_raycast	rc;

	rc.tex_width = 64;
	rc.tex_height = 64;
	rc.buffer = allocate_buffer(game);
	if (!rc.buffer)
		free_all_exit(game, EXIT_FAILURE, 1);
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		calculate_ray_for_pixel(&rc, game, x);
		calculate_line_height(&rc);
		calcul_textre_x(&rc, game);
		texture_wall(&rc, game);
		render_ceiling_and_floor(&rc, game, x);
		x++;
	}
	display_image(game, &rc);
}
