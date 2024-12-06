/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:17:18 by kenzo             #+#    #+#             */
/*   Updated: 2024/12/06 02:50:51 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static void	fill(int **map, int x, int y, t_game *game, int *valid)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height || !(*valid))
		return;
	if (map[y][x] == 1 || map[y][x] == 3)  // 1 = mur, 3 = zone visitée
		return;
	if (x == 0 || x == game->map_width - 1 || y == 0 || y == game->map_height - 1)
	{
		*valid = 0;
		return;
	}
	map[y][x] = 3;  // Marquer comme visité
	fill(map, x + 1, y, game, valid);
	fill(map, x - 1, y, game, valid);
	fill(map, x, y + 1, game, valid);
	fill(map, x, y - 1, game, valid);
}

int	is_flood_fill_valid(int **map, t_game *game)
{
	int	valid;

	valid = 1;
	fill(map, game->player_x, game->player_y, game, &valid);
	return (valid);
}

void	find_player(int **map, t_game *game)
{
	int	x;
	int	y;

	y = 0;
	game->player_found = 0;
	ft_printf("%d", game->map_height);
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			ft_printf("%d",map[y][x]);
			if (map[y][x] == 2)  // Le joueur est représenté par 2
			{
				if (game->player_found)
				{
					perror("Erreur : plusieurs joueurs détectés");
					free_all_exit(game, EXIT_FAILURE);
				}
				game->player_x = x;
				game->player_y = y;
				game->player_found = 1;
			}
			x++;
		}
		y++;
	}
	if (!game->player_found)
	{
		perror("Erreur : joueur non trouvé");
		free_all_exit(game, EXIT_FAILURE);
	}
}

void	validate_map_closed(int **map, t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if ((map[y][x] == 0 || map[y][x] == 2) &&  // 0 = vide, 2 = joueur
				(x == 0 || x == game->map_width - 1 || y == 0 || y == game->map_height - 1))
			{
				perror("Erreur : carte non fermée");
				exit(EXIT_FAILURE);
			}
			x++;
		}
		y++;
	}
}

void	parse_and_validate_map(int **map, t_game *game)
{
	find_player(map, game);
	ft_printf("da");
	print_map(game->map);
	validate_map_closed(map, game);
	if (!is_flood_fill_valid(map, game))
	{
		perror("Erreur : carte non valide (trou détecté)");
		free_all_exit(game, EXIT_FAILURE);
	}
	ft_printf("Carte valide et fermée\n");
}
