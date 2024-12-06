/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:17:18 by kenzo             #+#    #+#             */
/*   Updated: 2024/12/06 12:37:12 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	dfs(int x, int y, int **map, int width, int height, int visited[height][width])
{
	if (x < 0 || x >= width || y < 0 || y >= height)
	{
		write(2, "Error\nMap is open\n", 18);
		exit(1);
	}
	if (visited[y][x] || (map[y][x] != 0 && map[y][x] != 2))
		return ;
	visited[y][x] = 1;
	dfs(x + 1, y, map, width, height, visited);
	dfs(x - 1, y, map, width, height, visited);
	dfs(x, y + 1, map, width, height, visited);
	dfs(x, y - 1, map, width, height, visited);
}

void	check_map_closed(t_game *game)
{
	int	**map;
	int	width;
	int	height;
	int	visited[game->map->height][game->map->width];
	int	player_x;
	int	player_y;

	map = game->map->data;
	width = game->map->width;
	height = game->map->height;
	memset(visited, 0, sizeof(visited));
	player_x = (int)game->player.pos.x;
	player_y = (int)game->player.pos.y;
	if (player_x < 0 || player_x >= width || player_y < 0 || player_y >= height
		|| map[player_y][player_x] != 2)
	{
		write(2, "Error\nInvalid player position\n", 30);
		exit(1);
	}
	dfs(player_x, player_y, map, width, height, visited);
	game->map->data[player_y][player_x] = 0;
}
