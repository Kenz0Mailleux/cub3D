/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:05:58 by kenzo             #+#    #+#             */
/*   Updated: 2025/04/22 05:42:16 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	fill_map_cell(t_game *game, t_map *map, char c, t_vector pos)
{
	if (c == '1')
		map->data[(int)pos.y][(int)pos.x] = 1;
	else if (c == '0')
		map->data[(int)pos.y][(int)pos.x] = 0;
	else if (ft_strchr("NESW", c))
	{
		parse_player(game, map, pos, c);
		map->data[(int)pos.y][(int)pos.x] = 2;
	}
	else
		map->data[(int)pos.y][(int)pos.x] = 0;
}

void	populate_map_data(char **map_str,
	t_map *map, t_game *game, int start_index)
{
	int			y;
	t_vector	pos;
	char		*row;

	y = start_index;
	pos.y = 0;
	while (map_str[y])
	{
		pos.x = 0;
		row = map_str[y];
		while (row[(int)pos.x])
		{
			fill_map_cell(game, map, row[(int)pos.x], pos);
			pos.x++;
		}
		y++;
		pos.y++;
	}
}

void	verify_player_initialised(t_game *game)
{
	if (!game->player.initialised)
	{
		ft_printf("Erreur : Joueur manquant");
		free_all_exit(game, EXIT_FAILURE, 1);
	}
}

void	free_map_str(char **map_str)
{
	int	i;

	i = 0;
	if (!map_str)
		return ;
	while (map_str[i])
	{
		if (map_str[i])
			free(map_str[i]);
		i++;
	}
	free(map_str);
}

t_map	*parse_map(char *filename, t_game *game)
{
	char	**map_str;
	t_map	*map;
	int		width;
	int		height;
	int		start_index;

	map = init_map_struct();
	map_str = init_map_str(filename);
	start_index = parse_file(map, map_str, game);
	start_index += check_strings(&map_str[start_index]);
	if (start_index == -1)
	{
		ft_printf("Erreur : map invalide");
		free_all_exit(game, EXIT_FAILURE, 1);
	}
	calculate_map_dimensions(map_str, &width, &height, start_index);
	map->data = allocate_map(width, height, game);
	map->width = width;
	map->height = height;
	map->ground_color = parse_color(map->image[4].path);
	map->ceiling_color = parse_color(map->image[5].path);
	populate_map_data(map_str, map, game, start_index);
	verify_player_initialised(game);
	free_map_str(map_str);
	return (map);
}
