/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:00:41 by kenzo             #+#    #+#             */
/*   Updated: 2025/04/22 05:46:25 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	draw_scene(t_game *game)
{
	raycast_calcul(game);
}

int	close_window(t_game *game)
{
	ft_printf("Fermeture de la fenêtre demandée.\n");
	free_all_exit(game, EXIT_FAILURE, 1);
	return (0);
}

void	start_loop(t_game *game)
{
	mlx_hook(game->win_ptr, 2, 1L << 0, &handle_keypress, game);
	mlx_hook(game->win_ptr, 17, 0L, &close_window, game);
	draw_scene(game);
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
			free_all_exit(game, EXIT_FAILURE, 1);
		}
		start_loop(game);
		free_all_exit(game, EXIT_SUCCESS, 1);
	}
	return (EXIT_SUCCESS);
}
