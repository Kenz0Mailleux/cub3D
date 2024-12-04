/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:21:08 by kenzo             #+#    #+#             */
/*   Updated: 2024/12/01 23:42:27 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int **allocate_map(int width, int height, t_game *game)
{
	int **map;
	int i;

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

// Fonction pour libérer la carte
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

int ft_is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
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

char *find_path_in_file(char *str, t_game *game)
{
	int	i;
	int	j;
	char *str_path;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (ft_is_space(str[i]))
			i++;
		else
		{
			j = i;
			while (str[i])
			{
				i++;
			}
			//attention
			str_path = malloc(1000);
			str_path = ft_strncpy_gnl(str_path, &str[j], i - j);
			if (!str_path)
			{
				perror("erreur malloc");
				exit(1);
				free_all_exit(game, EXIT_FAILURE);
			}
			return (str_path);
		}
		i++;
	}
	return (NULL);
}

void init_map_image_path(t_map *map)
{
	map->image[0].path = NULL;
	map->image[1].path = NULL;
	map->image[2].path = NULL;
	map->image[3].path = NULL;
	map->image[4].path = NULL;
	map->image[5].path = NULL;
}

int	found_all(t_map *map)
{
	if (map->image[0].found == 1 && map->image[1].found == 1
		&& map->image[2].found == 1 && map->image[3].found == 1
		&& map->image[4].found == 1 && map->image[5].found == 1)
	{
		return (1);
	}
	else
		return (0);
}

int	parse_file(t_map *map, char **map_str, t_game *game)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	
	while (map_str[i])
	{
		j = 0;
		while (map_str[i][j])
		{
			if (ft_is_space(map_str[i][j]))
				j++;
			else if (ft_strncmp(&map_str[i][j], "NO ", 3) == 0)
			{	
				j += 2;
				if (map->image[0].path == NULL)
				{
					map->image[0].path = find_path_in_file(&map_str[i][j], game);
					map->image[0].found = 1;
				}
				else
				{
					perror("Erreur malloc");
					exit(1);
				}
			}
			else if (ft_strncmp(&map_str[i][j], "SO ", 3) == 0)
			{
				j += 2;
				if (map->image[1].path == NULL)
				{
					map->image[1].path = find_path_in_file(&map_str[i][j], game);
					map->image[1].found = 1;
				}
				else
				{
					perror("Erreur malloc");
					exit(1);
				}
			}
			else if (ft_strncmp(&map_str[i][j], "EA ", 3) == 0)
			{
				j += 2;
				if (map->image[2].path == NULL)
				{
					map->image[2].path = find_path_in_file(&map_str[i][j], game);
					map->image[2].found = 1;
				}
				else
				{
					perror("Erreur malloc");
					exit(1);
				}
			}
			else if (ft_strncmp(&map_str[i][j], "WE ", 3) == 0)
			{
				j += 2;
				if (map->image[3].path == NULL)
				{
					map->image[3].path = find_path_in_file(&map_str[i][j], game);
					map->image[3].found = 1;
				}
				else
				{
					perror("Erreur malloc");
					exit(1);
				}
			}
			else if (ft_strncmp(&map_str[i][j], "F ", 2) == 0)
			{
				j += 2;
				if (map->image[4].path == NULL)
				{
					map->image[4].path = find_path_in_file(&map_str[i][j], game);
					map->image[4].found = 1;
				}
				else
				{
					perror("Erreur malloc");
					exit(1);
				}
			}
			else if (ft_strncmp(&map_str[i][j], "C ", 2) == 0)
			{
				j += 2;
				if (map->image[5].path == NULL)
				{
					map->image[5].path = find_path_in_file(&map_str[i][j], game);
					map->image[5].found = 1;
				}
				else
					exit(1);
			}
			j++;
		}
		i++;
		if (found_all(map))
			return (i);
	}
	return (i);
}

int check_strings(char **array)
{
	int i;
	int j;

	i = 0;
	while (array[i] != NULL)
	{
		j = 0;
		while (array[i][j] != '\0')
		{ 
			if (!ft_is_space(array[i][j]))
			{
				//ft_printf("Found a non-space string: %s at %d\n", array[i], i);
				return (i);
			}
			j++;
		}
		i++;
	}
	return (-1);
}

t_map *parse_map(char *filename, t_game *game) 
{
	char **map_str;
	t_map *map;
	int width;
	int height;
	int len;
	int	i;
	int	y;
	int x;

	width = 0,
	height = 0;
	i = 0;
	map = malloc(sizeof(t_map));
	if (!map)
	{
		perror("Erreur malloc");
		exit(EXIT_FAILURE);
	}
	init_map_image_path(map);
	map_str = init_map_str(filename);
	i = parse_file(map, map_str, game);

	i = i + check_strings(&map_str[i]);
	if (i == -1)
	{
		perror("Erreur malloc");
		free_all_exit(game, EXIT_FAILURE);
	}
	y = i;
	while (map_str[i])
	{
		len = strlen(map_str[i]);
		if (len > width)
			width = len;
		height++;
		i++;
	}
	map->data = allocate_map(width, height, game);
	map->width = width;
	map->height = height;
	i = 0;
	x = 0;
	game->player.initialised = 0;
	while (map_str[y])
	{
		x = 0;
		while (map_str[y][x])
		{

			if (map_str[y][x] == '1')
				map->data[i][x] = 1;  // Mur
			else if (map_str[y][x] == '0')
			{
				map->data[i][x] = 0;  // Espace vide
			}
			else if (map_str[y][x] == 'N')
			{
				if (game->player.initialised)
				{
					perror("Maximum un joueur");
					free_all_exit(game, EXIT_FAILURE);
				}
				map->data[i][x] = 0;  // joueur NORD
				game->player.pos.y = i;
				game->player.pos.x = x;
				game->player.dir.x = 0;
				game->player.dir.y = -1;
				game->player.plane.x = 0.66;
				game->player.plane.y = 0;
				game->player.initialised = 1;
			}
			else if (map_str[y][x] == 'E')
			{
				if (game->player.initialised)
				{
					perror("Maximum un joueur");
					free_all_exit(game, EXIT_FAILURE);
				}
				map->data[i][x] = 0;  // joueur EST
				game->player.pos.y = i;
				game->player.pos.x = x;
				game->player.dir.x = 1;
				game->player.dir.y = 0;
				game->player.plane.x = 0;
				game->player.plane.y = 0.66;
				game->player.initialised = 1;
			}
			else if (map_str[y][x] == 'S')
			{
				if (game->player.initialised)
				{
					perror("Maximum un joueur");
					free_all_exit(game, EXIT_FAILURE);
				}
				map->data[i][x] = 0;  // joueur SUD
				game->player.pos.y = i;
				game->player.pos.x = x;
				game->player.dir.x = 0;
				game->player.dir.y = 1;
				game->player.plane.x = -0.66;
				game->player.plane.y = 0;
				game->player.initialised = 1;
			}
			else if (map_str[y][x] == 'W')
			{
				if (game->player.initialised)
				{
					perror("Maximum un joueur");
					free_all_exit(game, EXIT_FAILURE);
				}
				map->data[i][x] = 0;  // joueur WEST
				game->player.pos.y = i;
				game->player.pos.x = x;
				game->player.dir.x = -1;
				game->player.dir.y = 0;
				game->player.plane.x = 0;
				game->player.plane.y = -0.66;
				game->player.initialised = 1;
			}
			else
				map->data[i][x] = 0;
			x++;
		}
		y++;
		i++;
	}
	if (game->player.initialised == 0)
	{
		perror("Joueur manquant");
		exit(1);
		//free_all_exit(game, EXIT_FAILURE);
	}
	print_map(map);
	return (map);
}

void print_map(t_map *map)
{
	int y;
	int x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			ft_printf("%d ", map->data[y][x]);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}
