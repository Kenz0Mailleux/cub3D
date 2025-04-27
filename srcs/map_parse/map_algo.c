/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:17:18 by kenzo             #+#    #+#             */
/*   Updated: 2025/04/27 22:14:38 by kenzo            ###   ########.fr       */
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

void	dfs(t_vector pos, t_game *game, int **visited, t_vector size)
{
	int	y;
	int	x;

	x = (int)pos.x;
	y = (int)pos.y;
	if (x < 0 || x >= size.x || y < 0 || y >= size.y)
	{
		ft_printf("Erreur, map ouverte\n");
		free_all_exit(game, EXIT_FAILURE, 1);
	}
	if (game->map->data[y] == NULL || game->map->data[y][x] == -1)
	{
		ft_printf("Erreur, map ouverte\n");
		free_all_exit(game, EXIT_FAILURE, 1);
	}
	if (visited[y][x] || (game->map->data[y][x] != 0 && \
			game->map->data[y][x] != 2))
		return ;
	visited[y][x] = 1;
	dfs((t_vector){x + 1, y}, game, visited, size);
	dfs((t_vector){x - 1, y}, game, visited, size);
	dfs((t_vector){x, y + 1}, game, visited, size);
	dfs((t_vector){x, y - 1}, game, visited, size);
}

void	check_map_closed(t_game *game)
	{
	int			**visited;
	t_vector	pos;
	t_vector	size;

	size.x = game->map->width;
	size.y = game->map->height;
	pos.x = (int)game->player.pos.x;
	pos.y = (int)game->player.pos.y;
	if (pos.x < 0 || pos.x >= size.x || pos.y < 0 || pos.y >= size.y
		|| game->map->data[(int)pos.y][(int)pos.x] != 2)
	{
		ft_printf("Position invalide");
		free_all_exit(game, EXIT_FAILURE, 1);
	}
	visited = allocate_visited(size.y, size.x);
	if (!visited)
		free_all_exit(game, EXIT_FAILURE, 1);
	dfs(pos, game, visited, size);
	free_visited(visited, size.y);
	game->map->data[(int)pos.y][(int)pos.x] = 0;
}
