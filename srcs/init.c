/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:48:16 by kenzo             #+#    #+#             */
/*   Updated: 2024/12/06 02:58:49 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void init_image_paths(t_game *game)
{
	game->images[0].path = game->map->image[0].path;
	game->images[1].path = game->map->image[1].path;
	game->images[2].path = game->map->image[2].path;
	game->images[3].path = game->map->image[3].path;
}

void load_textures(t_game *game, int width, int height)
{
	game->images[0].img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, game->map->image[0].path, &width, &height);
	if (!game->images[0].img_ptr)
		free_all_exit(game, EXIT_FAILURE);
	game->images[1].img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,  game->map->image[1].path, &width, &height);
	if (!game->images[1].img_ptr)
		free_all_exit(game, EXIT_FAILURE);
	game->images[2].img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, game->map->image[2].path, &width, &height);
	if (!game->images[2].img_ptr)
		free_all_exit(game, EXIT_FAILURE);
	game->images[3].img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, game->map->image[3].path, &width, &height);
	if (!game->images[3].img_ptr)
		free_all_exit(game, EXIT_FAILURE);
	
}

void	fill_image(void *img_ptr, int width, int height, int color)
{
	char	*buffer;
	int		bpp;
	int		line_size;
	int		endian;
	int		x;
	int		y;

	buffer = mlx_get_data_addr(img_ptr, &bpp, &line_size, &endian);
	if (!buffer)
		return ;
	bpp /= 8;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			*(unsigned int *)(buffer + y * line_size + x * bpp) = color;
			x++;
		}
		y++;
	}
}

t_game *init_game(char *path, int width, int height, char *title)
{
	t_game *game;

	game = malloc(sizeof(t_game));
	if (!game)
		free_all_exit(game, EXIT_FAILURE);
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		free_all_exit(game, EXIT_FAILURE);
	game->win_ptr = mlx_new_window(game->mlx_ptr, width, height, title);
	if (!game->win_ptr)
		free_all_exit(game, EXIT_FAILURE);
	game->player.initialised = 0;
	game->map = parse_map(path, game);
	game->player.pos.x += 0.5;
	game->player.pos.y += 0.5;
	init_image_paths(game);
	load_textures(game, width, height);
	return (game);
}
