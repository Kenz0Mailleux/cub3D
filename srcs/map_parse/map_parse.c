/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:21:08 by kenzo             #+#    #+#             */
/*   Updated: 2024/12/06 12:38:52 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

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

static void parse_texture_line(t_map *map, char *line, t_game *game, int id, char *identifier)
{
	int j;

	j = 0;
	while (ft_isspace(line[j]))
		j++;
	if (ft_strncmp(&line[j], identifier, ft_strlen(identifier)) == 0)
	{
		j += ft_strlen(identifier) - 1;
		if (map->image[id].path == NULL)
		{
			if (id >= 0 && id < 4)
				map->image[id].path = find_path_textures_in_file(&line[j], game);
			else
				map->image[id].path = find_path_color_in_file(&line[j], game);
			map->image[id].found = 1;
		}
		else
		{
			perror("Erreur file");
			exit(1);
		}
	}
}

static void parse_line(t_map *map, char *line, t_game *game)
{
	parse_texture_line(map, line, game, 0, "NO ");
	parse_texture_line(map, line, game, 1, "SO ");
	parse_texture_line(map, line, game, 2, "EA ");
	parse_texture_line(map, line, game, 3, "WE ");
	parse_texture_line(map, line, game, 4, "F ");
	parse_texture_line(map, line, game, 5, "C ");
}

int parse_file(t_map *map, char **map_str, t_game *game)
{
	int i;

	i = 0;
	while (map_str[i])
	{
		parse_line(map, map_str[i], game);
		i++;
		if (found_all(map))
			return (i);
	}
	return (i);
}

static t_map	*init_map_struct(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
	{
		perror("Erreur malloc");
		exit(EXIT_FAILURE);
	}
	init_map_image_path(map);
	return (map);
}

static void	calculate_map_dimensions(char **map_str, int *width, int *height, int start_index)
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

static void	set_player_direction(t_game *game, char c)
{
	if (c == 'N')
	{
		game->player.dir.x = 0;
		game->player.dir.y = -1;
		game->player.plane.x = 0.66;
		game->player.plane.y = 0;
	}
	if (c == 'E')
	{
		game->player.dir.x = 1;
		game->player.dir.y = 0;
		game->player.plane.x = 0;
		game->player.plane.y = 0.66;
	}
	if (c == 'S')
	{
		game->player.dir.x = 0;
		game->player.dir.y = 1;
		game->player.plane.x = -0.66;
		game->player.plane.y = 0;
	}
	if (c == 'W')
	{
		game->player.dir.x = -1;
		game->player.dir.y = 0;
		game->player.plane.x = 0;
		game->player.plane.y = -0.66;
	}
}

static void	parse_player(t_game *game, t_map *map, int x, int y, char c)
{
	if (game->player.initialised)
	{
		perror("Erreur : Maximum un joueur");
		free_all_exit(game, EXIT_FAILURE);
	}
	game->player.initialised = 1;
	game->player.pos.x = x;
	game->player.pos.y = y;
	map->data[y][x] = 0;
	set_player_direction(game, c);
}

static void	fill_map_cell(t_game *game, t_map *map, char c, int x, int y)
{
	if (c == '1')
		map->data[y][x] = 1;
	else if (c == '0')
		map->data[y][x] = 0;
	else if (ft_strchr("NESW", c))
	{
		parse_player(game, map, x, y, c);
		map->data[y][x] = 2;
	}
	else
		map->data[y][x] = 0;
}

static void	populate_map_data(char **map_str,
	t_map *map, t_game *game, int start_index)
{
	int		x;
	int		y;
	int		i;
	char	*row;

	y = start_index;
	i = 0;
	while (map_str[y])
	{
		x = 0;
		row = map_str[y];
		while (row[x])
		{
			fill_map_cell(game, map, row[x], x, i);
			x++;
		}
		y++;
		i++;
	}
	ft_printf("%d", game->player.pos.y);
	ft_printf("%d", game->player.pos.x);
	print_map(map);
}

static void	verify_player_initialised(t_game *game)
{
	if (!game->player.initialised)
	{
		perror("Erreur : Joueur manquant");
		free_all_exit(game, EXIT_FAILURE);
	}
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
		perror("Erreur : map invalide");
		free_all_exit(game, EXIT_FAILURE);
	}
	calculate_map_dimensions(map_str, &width, &height, start_index);
	map->data = allocate_map(width, height, game);
	map->width = width;
	map->height = height;
	map->ground_color = parse_color(map->image[4].path);
	map->ceiling_color = parse_color(map->image[5].path);
	populate_map_data(map_str, map, game, start_index);
	verify_player_initialised(game);
	return (map);
}
