/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:00:41 by kenzo             #+#    #+#             */
/*   Updated: 2025/04/18 05:36:03 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	free_all_exit(t_game *game, int succes)
{
	int	i;

	i = 0;
	ft_printf("Free error");
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
		//free_map(game->map->data, game->map->height);
		free(game->map);
		free(game);
	}
	exit(succes);
}

void	draw_scene(t_game *game)
{
	raycast_calcul(game);
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
