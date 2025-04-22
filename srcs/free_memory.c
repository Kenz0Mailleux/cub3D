/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:06:29 by kenzo             #+#    #+#             */
/*   Updated: 2025/04/22 06:02:14 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	free_map(int **map, int height)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < height)
	{
		if (map[i] != NULL)
			free(map[i]);
		i++;
	}
	free(map);
}

void	free_images(t_game *game)
{
	int	i;

	if (!game || !game->map->image)
		return ;
	i = 0;
	while (i < 6)
	{
		if (game->map->image[i].path)
		{
			free(game->map->image[i].path);
			game->map->image[i].path = NULL;
		}
		i++;
	}
}

void	free_data(int **data, int height)
{
	int	i;

	i = 0;
	if (!data)
		return ;
	while (i < height)
	{
		if (data[i] != NULL)
		{
			free(data[i]);
			data[i] = NULL;
		}
		i++;
	}
	free(data);
	data = NULL;
}

void	free_graphics(t_game *game)
{
	int	i;

	i = 0;
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
}

void	free_all_exit(t_game *game, int success, int free_mlx)
{
	if (game)
	{
		if (free_mlx)
		{
			free_graphics(game);
			free_images(game);
			if (game->map)
			{
				free_data(game->map->data, game->map->height);
				free(game->map);
			}
		}
		free(game);
	}
	exit(success);
}

// void	free_all_exit(t_game *game, int success)
// {
// 	int	i;

// 	i = 0;
// 	ft_printf("Free error\n");
// 	if (game)
// 	{
// 		if (game->mlx_ptr)
// 		{
// 			while (i < 4)
// 			{
// 				if (game->images[i].img_ptr)
// 					mlx_destroy_image(game->mlx_ptr, game->images[i].img_ptr);
// 				i++;
// 			}
// 			if (game->win_ptr)
// 				mlx_destroy_window(game->mlx_ptr, game->win_ptr);
// 			mlx_destroy_display(game->mlx_ptr);
// 			free(game->mlx_ptr);
// 		}
// 		free_images(game);
// 		if (game->map)
// 		{
// 			free_data(game->map->data, game->map->height);
// 			free(game->map);
// 		}
// 		free(game);
// 	}
// 	exit(success);
// }
