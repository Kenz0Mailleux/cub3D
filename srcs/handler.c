/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 20:07:19 by kenzo             #+#    #+#             */
/*   Updated: 2025/03/17 15:27:46 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	move_forward(t_game *game)
{
	if (game->map->data[(int)(game->player.pos.y)]
		[(int)(game->player.pos.x + game->player.dir.x * MOVE_SPEED)] == 0)
		game->player.pos.x += game->player.dir.x * MOVE_SPEED;
	if (game->map->data[(int)(game->player.pos.y + \
		game->player.dir.y * MOVE_SPEED)]
		[(int)game->player.pos.x] == 0)
		game->player.pos.y += game->player.dir.y * MOVE_SPEED;
}

int	handle_movement(int keycode, t_game *game)
{
	if (keycode == KEY_Z)
		move_forward(game);
	else if (keycode == KEY_S)
	{
		if (game->map->data[(int)(game->player.pos.y)]
		[(int)(game->player.pos.x - game->player.dir.x * MOVE_SPEED)] == 0)
			game->player.pos.x -= game->player.dir.x * MOVE_SPEED;
		if (game->map->data[(int)(game->player.pos.y - \
			game->player.dir.y * MOVE_SPEED)]
			[(int)game->player.pos.x] == 0)
			game->player.pos.y -= game->player.dir.y * MOVE_SPEED;
	}
	return (0);
}

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir.x;
	old_plane_x = game->player.plane.x;
	game->player.dir.x = game->player.dir.x * cos(-ROT_SPEED)
		- game->player.dir.y * sin(-ROT_SPEED);
	game->player.dir.y = old_dir_x * sin(-ROT_SPEED)
		+ game->player.dir.y * cos(-ROT_SPEED);
	game->player.plane.x = game->player.plane.x * cos(-ROT_SPEED)
		- game->player.plane.y * sin(-ROT_SPEED);
	game->player.plane.y = old_plane_x * sin(-ROT_SPEED)
		+ game->player.plane.y * cos(-ROT_SPEED);
}

int	handle_rotation(int keycode, t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	if (keycode == KEY_Q)
		rotate_left(game);
	else if (keycode == KEY_D)
	{
		old_dir_x = game->player.dir.x;
		old_plane_x = game->player.plane.x;
		game->player.dir.x = game->player.dir.x * cos(ROT_SPEED)
			- game->player.dir.y * sin(ROT_SPEED);
		game->player.dir.y = old_dir_x * sin(ROT_SPEED)
			+ game->player.dir.y * cos(ROT_SPEED);
		game->player.plane.x = game->player.plane.x * cos(ROT_SPEED)
			- game->player.plane.y * sin(ROT_SPEED);
		game->player.plane.y = old_plane_x * sin(ROT_SPEED)
			+ game->player.plane.y * cos(ROT_SPEED);
	}
	return (0);
}

int	handle_keypress(int keycode, t_game *game)
{
	printf("%f ", game->player.pos.y);
	printf("%f\n", game->player.pos.x);
	if (keycode == KEY_ESCAPE)
		free_all_exit(game, EXIT_FAILURE);
	handle_movement(keycode, game);
	handle_rotation(keycode, game);
	draw_scene(game);
	return (0);
}
