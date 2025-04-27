/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:30:29 by kenzo             #+#    #+#             */
/*   Updated: 2025/04/27 22:41:33 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	set_player_direction_x(t_game *game, char c)
{
	if (c == 'E')
	{
		game->player.dir.x = 1;
		game->player.plane.x = 0;
	}
	else if (c == 'W')
	{
		game->player.dir.x = -1;
		game->player.plane.x = 0;
	}
	else
	{
		game->player.dir.x = 0;
		if (c == 'N')
			game->player.plane.x = 0.66;
		else
			game->player.plane.x = -0.66;
	}
}

void	set_player_direction(t_game *game, char c)
{
	set_player_direction_x(game, c);
	if (c == 'N')
	{
		game->player.dir.y = -1;
		game->player.plane.y = 0;
	}
	else if (c == 'S')
	{
		game->player.dir.y = 1;
		game->player.plane.y = 0;
	}
	else
	{
		game->player.dir.y = 0;
		if (c == 'E')
			game->player.plane.y = 0.66;
		else
			game->player.plane.y = -0.66;
	}
}

void	parse_player(t_game *game, t_map *map, t_vector pos, char c)
{
	if (game->player.initialised)
	{
		ft_printf("Erreur : Maximum un joueur.\n");
		free_all_exit(game, EXIT_FAILURE, 1);
	}
	game->player.initialised = 1;
	game->player.pos.x = pos.x;
	game->player.pos.y = pos.y;
	map->data[(int)pos.y][(int)pos.x] = 0;
	set_player_direction(game, c);
}
