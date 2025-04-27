/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:05:54 by kenzo             #+#    #+#             */
/*   Updated: 2025/04/27 22:41:22 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

// int	parse_file(t_map *map, char **map_str, t_game *game)
// {
// 	int	i;
// 	int	start;

// 	i = 0;
// 	while (map_str[i])
// 	{
// 		parse_line(map, map_str[i], game);
// 		i++;
// 		if (found_all(map))
// 		{
// 			while (map_str[i] && ft_isempty_line(map_str[i]))
// 				i++;
// 			start = i;
// 			while (map_str[i])
// 			{
// 				if (ft_is_map_line(map_str[i]))
// 					i++;
// 				else
// 				{
// 					ft_printf("Erreur : Ligne invalide");
// 					exit(EXIT_FAILURE);
// 				}
// 			}
// 			return (start);
// 		}
// 	}
// 	ft_printf("Erreur : Textures manquantes ou incomplètes");
// 	exit(EXIT_FAILURE);
// }

int	find_map_start(t_game *game, char **map_str, int i)
{
	int	start;

	while (map_str[i] && ft_isempty_line(map_str[i]))
		i++;
	start = i;
	while (map_str[i])
	{
		if (!map_str[i])
		{
			ft_printf("Ligne invalide\n");
			free_all_exit(game, EXIT_FAILURE, 0);
		}
		if (!ft_is_map_line(map_str[i]))
		{
			ft_printf("Ligne invalide\n");
			free_all_exit(game, EXIT_FAILURE, 0);
		}
		i++;
	}
	return (start);
}

int	parse_file(t_map *map, char **map_str, t_game *game)
{
	int	i;

	if (!map_str)
	{
		ft_printf("Map inexistante\n");
		free_all_exit(game, EXIT_FAILURE, 0);
	}
	i = 0;
	while (map_str[i])
	{
		parse_line(map, map_str[i], game);
		i++;
		if (found_all(map))
			return (find_map_start(game, map_str, i));
	}
	ft_printf("Erreur : Textures manquantes ou incomplètes.\n");
	free_all_exit(game, EXIT_FAILURE, 1);
	return (0);
}

t_map	*init_map_struct(t_game *game)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		free_all_exit(game, EXIT_FAILURE, 1);
	init_map_image_path(map);
	return (map);
}

void	calculate_map_dimensions(char **map_str, int *width, \
		int *height, int start_index)
{
	int	len;

	*width = 0;
	*height = 0;
	while (map_str[start_index])
	{
		len = strlen(map_str[start_index]);
		if (len > *width)
			*width = len;
		(*height)++;
		start_index++;
	}
}
