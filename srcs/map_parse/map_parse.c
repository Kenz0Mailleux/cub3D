/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:21:08 by kenzo             #+#    #+#             */
/*   Updated: 2025/04/27 22:52:17 by kenzo            ###   ########.fr       */
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

int	parse_texture_line(t_dir_parse *parse, char *line, int id, char *identifier)
{
	int	j;

	j = 0;
	while (ft_isspace(line[j]))
		j++;
	if (ft_strncmp(&line[j], identifier, ft_strlen(identifier)) == 0)
	{
		j += ft_strlen(identifier);
		if (parse->map->image[id].path == NULL)
		{
			if (id >= 0 && id < 4)
				parse->map->image[id].path = \
					find_path_textures_in_file(&line[j], parse->game);
			else
				parse->map->image[id].path = \
					find_path_color_in_file(&line[j], parse->game);
			parse->map->image[id].found = 1;
			return (1);
		}
		ft_printf("Erreur: un coté a deux textures.\n");
		free_all_exit(parse->game, EXIT_FAILURE, 1);
	}
	return (0);
}

void	parse_line(t_map *map, char *line, t_game *game)
{
	int			valid_key;
	t_dir_parse	parse;

	parse.map = map;
	parse.game = game;
	valid_key = 0;
	valid_key += parse_texture_line(&parse, line, 0, "NO ");
	valid_key += parse_texture_line(&parse, line, 1, "SO ");
	valid_key += parse_texture_line(&parse, line, 2, "EA ");
	valid_key += parse_texture_line(&parse, line, 3, "WE ");
	valid_key += parse_texture_line(&parse, line, 4, "F ");
	valid_key += parse_texture_line(&parse, line, 5, "C ");
	if (valid_key == 0)
	{
		ft_printf("Erreur : Clé invalide dans le fichier.\n");
		free_all_exit(game, EXIT_FAILURE, 1);
	}
}

int	ft_isempty_line(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (0);
		line++;
	}
	return (1);
}

int	ft_is_map_line(char *line)
{
	if (!line)
		return (0);
	while (*line != '\0')
	{
		if (ft_strchr(" \t01NESW\n", *line))
			line++;
		else
			return (0);
	}
	return (1);
}
