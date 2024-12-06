/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_memory.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 01:42:36 by kenzo             #+#    #+#             */
/*   Updated: 2024/12/06 02:39:01 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void init_map_image_path(t_map *map)
{
	map->image[0].path = NULL;
	map->image[1].path = NULL;
	map->image[2].path = NULL;
	map->image[3].path = NULL;
	map->image[4].path = NULL;
	map->image[5].path = NULL;
}

int **allocate_map(int width, int height, t_game *game)
{
	int	**map;
	int	i;

	map = (int **)malloc(sizeof(int *) * height);
	if (!map)
	{
		perror("Erreur d'allocation de la carte");
		exit(EXIT_FAILURE);
		free_all_exit(game, EXIT_FAILURE);
	}

	i = 0;
	while (i < height)
	{
		map[i] = (int *)malloc(sizeof(int) * width);
		if (!map[i])
		{
			perror("Erreur d'allocation d'une ligne de la carte");
			exit(EXIT_FAILURE);
			//free_all_exit(game, EXIT_FAILURE)
		}
		i++;
	}
	return (map);
}

void free_map(int **map, int height)
{
	int i;

	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	map_alloc_size(const char *filename)
{
	char	*str;
	int		file;
	int		i;

	i = 0;
	file = open(filename, O_RDONLY);
	str	= get_next_line(file);
	while (str)
	{
		free(str);
		str = get_next_line(file);
		i++;
	}
	close(file);
	return (i);
}

char	**init_map_str(const char *filename)
{
	char	**map_str;
	char	*str;
	int		file;
	int		map_size;
	int		i;

	map_size = map_alloc_size(filename);
	map_str = malloc(sizeof(char *) * (map_size + 1));
	file = open(filename, O_RDONLY);
	str	= get_next_line(file);
	i = 0;

	ft_printf(map_str[i]);
	while (str)
	{
		map_str[i] = str;
		str	= get_next_line(file);
		i++;
	}
	close(file);
	return (map_str);
}
