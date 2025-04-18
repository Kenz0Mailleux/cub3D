/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:17:18 by kenzo             #+#    #+#             */
/*   Updated: 2025/04/18 06:01:25 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:17:18 by kenzo             #+#    #+#             */
/*   Updated: 2025/04/18 06:00:00 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static int	**allocate_visited(int height, int width)
{
	int	**visited;
	int	i;
	int	j;

	i = 0;
	visited = malloc(sizeof(int *) * height);
	if (!visited)
		return (NULL);
	while (i < height)
	{
		visited[i] = calloc(width, sizeof(int));
		if (!visited[i])
		{
			j = i - 1;
			while (j >= 0)
			{
				free(visited[j]);
				j--;
			}
			free(visited);
			return (NULL);
		}
		i++;
	}
	return (visited);
}

static void	free_visited(int **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

void	dfs(t_vector pos, t_vector size, int **map, int **visited)
{
	int	x;
	int	y;

	x = (int)pos.x;
	y = (int)pos.y;
	if (x < 0 || x >= size.x || y < 0 || y >= size.y)
	{
		write(2, "Error\nMap is open\n", 18);
		exit(1);
	}
	if (visited[y][x] || (map[y][x] != 0 && map[y][x] != 2))
		return ;
	visited[y][x] = 1;
	dfs((t_vector){x + 1, y}, size, map, visited);
	dfs((t_vector){x - 1, y}, size, map, visited);
	dfs((t_vector){x, y + 1}, size, map, visited);
	dfs((t_vector){x, y - 1}, size, map, visited);
}

void	check_map_closed(t_game *game)
{
	int			**visited;
	int			**map;
	t_vector	pos;
	t_vector	size;

	map = game->map->data;
	size.x = game->map->width;
	size.y = game->map->height;
	pos.x = (int)game->player.pos.x;
	pos.y = (int)game->player.pos.y;
	if (pos.x < 0 || pos.x >= size.x || pos.y < 0 || pos.y >= size.y
		|| map[(int)pos.y][(int)pos.x] != 2)
	{
		write(2, "Error\nInvalid player position\n", 30);
		free_all_exit(game, EXIT_FAILURE);
	}
	visited = allocate_visited(size.y, size.x);
	if (!visited)
	{
		write(2, "Error\nMalloc failed\n", 21);
		free_all_exit(game, EXIT_FAILURE);
	}
	dfs(pos, size, map, visited);
	free_visited(visited, size.y);
	game->map->data[(int)pos.y][(int)pos.x] = 0;
}
