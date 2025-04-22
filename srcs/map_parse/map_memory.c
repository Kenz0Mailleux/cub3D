/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_memory.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 01:42:36 by kenzo             #+#    #+#             */
/*   Updated: 2025/04/22 05:42:16 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	init_map_image_path(t_map *map)
{
	map->image[0].path = NULL;
	map->image[1].path = NULL;
	map->image[2].path = NULL;
	map->image[3].path = NULL;
	map->image[4].path = NULL;
	map->image[5].path = NULL;
}

int	**allocate_map(int width, int height, t_game *game)
{
	int	**map;
	int	i;

	map = (int **)malloc(sizeof(int *) * height);
	if (!map)
	{
		ft_printf("Erreur d'allocation de la carte");
		free_all_exit(game, EXIT_FAILURE, 1);
	}
	i = 0;
	while (i < height)
	{
		map[i] = (int *)malloc(sizeof(int) * width);
		if (!map[i])
		{
			ft_printf("Erreur d'allocation d'une ligne de la carte");
			while (i-- > 0)
				free(map[i]);
			free(map);
			free_all_exit(game, EXIT_FAILURE, 1);
		}
		i++;
	}
	return (map);
}

int	map_alloc_size(const char *filename)
{
	char	*str;
	int		file;
	int		i;

	i = 0;
	file = open(filename, O_RDONLY);
	str = get_next_line(file);
	while (str)
	{
		free(str);
		str = get_next_line(file);
		i++;
	}
	close(file);
	return (i);
}

static void	free_map_str(char **map_str, int i, int file)
{
	while (i > 0)
		free(map_str[--i]);
	free(map_str);
	close(file);
}

char	**init_map_str(const char *filename)
{
	char	**map_str;
	char	*str;
	int		file;
	int		map_size;
	int		i;

	i = 0;
	map_size = map_alloc_size(filename);
	map_str = malloc(sizeof(char *) * (map_size + 1));
	if (!map_str)
		return (NULL);
	file = open(filename, O_RDONLY);
	if (file < 0)
		return (free(map_str), NULL);
	str = get_next_line(file);
	while (str)
	{
		map_str[i] = ft_strdup(str);
		free(str);
		if (!map_str[i++])
			return (free_map_str(map_str, i, file), NULL);
		str = get_next_line(file);
	}
	map_str[i] = NULL;
	return (close(file), map_str);
}

// char	**init_map_str(const char *filename)
// {
// 	char	**map_str;
// 	char	*str;
// 	int		file;
// 	int		map_size;
// 	int		i;

// 	map_size = map_alloc_size(filename);
// 	map_str = malloc(sizeof(char *) * (map_size + 1));
// 	if (!map_str)
// 		return (NULL);
// 	file = open(filename, O_RDONLY);
// 	if (file < 0)
// 		return (free(map_str), NULL);
// 	str = get_next_line(file);
// 	i = 0;
// 	while (str)
// 	{
// 		map_str[i] = ft_strdup(str);
// 		if (!map_str[i])
// 		{
// 			free(str);
// 			while (i > 0)
// 				free(map_str[--i]);
// 			free(map_str);
// 			close(file);
// 			return (NULL);
// 		}
// 		free(str);
// 		str = get_next_line(file);
// 		i++;
// 	}
// 	map_str[i] = NULL;
// 	close(file);
// 	return (map_str);
// }
