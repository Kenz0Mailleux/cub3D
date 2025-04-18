/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:17:18 by kenzo             #+#    #+#             */
/*   Updated: 2025/04/18 04:53:57 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	dfs(t_vector pos, t_vector size, int **map, \
	int visited[(int)size.y][(int)size.x])
{
	if (pos.x < 0 || pos.x >= size.x || pos.y < 0 || pos.y >= size.y)
	{
		write(2, "Error\nMap is open\n", 18);
		exit(1);
	}
	if (visited[(int)pos.y][(int)pos.x] || \
		(map[(int)pos.y][(int)pos.x] != 0 && map[(int)pos.y][(int)pos.x] != 2))
		return ;
	visited[(int)pos.y][(int)pos.x] = 1;
	dfs((t_vector){pos.x + 1, pos.y}, size, map, visited);
	dfs((t_vector){pos.x - 1, pos.y}, size, map, visited);
	dfs((t_vector){pos.x, pos.y + 1}, size, map, visited);
	dfs((t_vector){pos.x, pos.y - 1}, size, map, visited);
}

void	check_map_closed(t_game *game)
{
	int			**map;
	int			visited[game->map->height][game->map->width];
	t_vector	pos;
	t_vector	size;

	map = game->map->data;
	size.x = game->map->width;
	size.y = game->map->height;
	memset(visited, 0, sizeof(visited));
	pos.x = (int)game->player.pos.x;
	pos.y = (int)game->player.pos.y;
	if (pos.x < 0 || pos.x >= size.x || pos.y < 0 || pos.y >= size.y
		|| map[(int)pos.y][(int)pos.x] != 2)
	{
		write(2, "Error\nInvalid player position\n", 30);
		free_all_exit(game, EXIT_FAILURE);
	}
	dfs(pos, size, map, visited);
	game->map->data[(int)pos.y][(int)pos.x] = 0;
}
