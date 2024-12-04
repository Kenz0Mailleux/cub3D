/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:00:41 by kenzo             #+#    #+#             */
/*   Updated: 2024/12/04 18:57:07 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "cub3D.h"

void	free_all_exit(t_game *game, int succes)
{
	int	i;

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
	exit(succes);
}

void	draw_scene(t_game *game)
{
	raycast_calcul(game);
}

int	handle_movement(int keycode, t_game *game)
{
	if (keycode == KEY_Z)
	{
		if (game->map->data[(int)(game->player.pos.y)]
			[(int)(game->player.pos.x + game->player.dir.x * MOVE_SPEED)] == 0)
			game->player.pos.x += game->player.dir.x * MOVE_SPEED;
		if (game->map->data[(int)(game->player.pos.y + game->player.dir.y * MOVE_SPEED)]
			[(int)game->player.pos.x] == 0)
			game->player.pos.y += game->player.dir.y * MOVE_SPEED; 
	}
	if (keycode == KEY_S)
	{
		if (game->map->data[(int)(game->player.pos.y)]
			[(int)(game->player.pos.x - game->player.dir.x * MOVE_SPEED)] == 0)
			game->player.pos.x -= game->player.dir.x * MOVE_SPEED;
		if (game->map->data[(int)(game->player.pos.y - game->player.dir.y * MOVE_SPEED)]
			[(int)game->player.pos.x] == 0)
			game->player.pos.y -= game->player.dir.y * MOVE_SPEED;
	}
	return 0;
}

int	handle_rotation(int keycode, t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	if (keycode == KEY_Q)
	{
		old_dir_x = game->player.dir.x;
		old_plane_x = game->player.plane.x;
		game->player.dir.x = game->player.dir.x * cos(-ROT_SPEED) - game->player.dir.y * sin(-ROT_SPEED);
		game->player.dir.y = old_dir_x * sin(-ROT_SPEED) + game->player.dir.y * cos(-ROT_SPEED);
		game->player.plane.x = game->player.plane.x * cos(-ROT_SPEED) - game->player.plane.y * sin(-ROT_SPEED);
		game->player.plane.y = old_plane_x * sin(-ROT_SPEED) + game->player.plane.y * cos(-ROT_SPEED);
	}
	if (keycode == KEY_D)
	{
		old_dir_x = game->player.dir.x;
		old_plane_x = game->player.plane.x;
		game->player.dir.x = game->player.dir.x * cos(ROT_SPEED) - game->player.dir.y * sin(ROT_SPEED);
		game->player.dir.y = old_dir_x * sin(ROT_SPEED) + game->player.dir.y * cos(ROT_SPEED);
		game->player.plane.x = game->player.plane.x * cos(ROT_SPEED) - game->player.plane.y * sin(ROT_SPEED);
		game->player.plane.y = old_plane_x * sin(ROT_SPEED) + game->player.plane.y * cos(ROT_SPEED);
	}
	return 0;
}

int	handle_keypress(int keycode, t_game *game)
{
	ft_printf("%d", keycode);
	if (keycode == KEY_ESCAPE)
		free_all_exit(game, EXIT_FAILURE);
	handle_movement(keycode, game);
	handle_rotation(keycode, game);
	draw_scene(game);
	return 0;
}


int	close_window(t_game *game)
{
	ft_printf("Fermeture de la fenêtre demandée.\n");
	free_all_exit(game, EXIT_FAILURE);
	return (0);
}


void	start_loop(t_game *game)
{
	draw_scene(game);
	mlx_hook(game->win_ptr, 2, 1L << 0, &handle_keypress, game);
	//mlx_hook(game->win_ptr, MLX_KEY_RELEASE, 1L << 1, &handle_keyrelease, game);
	mlx_hook(game->win_ptr, 17, 0L, &close_window, game);

	mlx_loop(game->mlx_ptr);
}

int	main(int argc, char *argv[])
{
	t_game	*game;

	if (argc == 2)
	{
		game = init_game(argv[1], SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
		if (!game->map)
		{
			ft_printf("Error: Failed to load the map file.\n");
			free_all_exit(game, EXIT_FAILURE);
		}
		start_loop(game);
		free_all_exit(game, EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

/*

si deux value, pas bon
duplicate pas bon
whitespace is ok
couleur rgb, 0 à 255 -> faire gaffe aux normes, virgule into espace pour etre sur de pas avoir de soucis

faire un algo pour la map, fermée correctement, checké les values, parsé le spawn (N E O S) pour l'endroit vers lequel le perso regarde


*/