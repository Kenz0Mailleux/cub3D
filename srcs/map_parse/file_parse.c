/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 01:49:58 by kenzo             #+#    #+#             */
/*   Updated: 2025/04/22 06:10:33 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

char	*extract_texture_path(char *str, int start, int end, t_game *game)
{
	char	*str_path;

	str_path = malloc(sizeof(char) * (end - start + 1));
	if (!str_path)
	{
		ft_printf("Erreur malloc\n");
		free_all_exit(game, EXIT_FAILURE, 1);
	}
	ft_strncpy_cb(str_path, &str[start], end - start);
	return (str_path);
}

char	*find_path_textures_in_file(char *str, t_game *game)
{
	int		i;
	int		j;
	char	*str_path;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			i++;
		else
		{
			j = i;
			while (str[i] && !ft_isspace(str[i]))
				i++;
			str_path = extract_texture_path(str, j, i, game);
			while (str[i] && ft_isspace(str[i]))
			{
				if (str[i] == '\n')
					return (str_path);
				i++;
			}
			free_all_exit(game, EXIT_FAILURE, 1);
		}
	}
	return (NULL);
}

int	skip_digits_and_comma(char *str, int i)
{
	if (!ft_isdigit((unsigned char)str[i]))
		return (-1);
	while (str[i] && ft_isdigit((unsigned char)str[i]))
		i++;
	if (str[i++] != ',')
		return (-1);
	return (i);
}

int	validate_color_format(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace((unsigned char)str[i]))
		i++;
	i = skip_digits_and_comma(str, i);
	if (i == -1)
		return (-1);
	while (str[i] && ft_isspace((unsigned char)str[i]))
		i++;
	i = skip_digits_and_comma(str, i);
	if (i == -1)
		return (-1);
	while (str[i] && ft_isspace((unsigned char)str[i]))
		i++;
	if (!ft_isdigit((unsigned char)str[i]))
		return (-1);
	while (str[i] && ft_isdigit((unsigned char)str[i]))
		i++;
	while (str[i] && ft_isspace((unsigned char)str[i]))
		i++;
	if (str[i] != '\0')
		return (-1);
	return (0);
}

char	*find_path_color_in_file(char *str, t_game *game)
{
	char	*result;

	if (validate_color_format(str) == -1)
	{
		ft_printf("Erreur : format de couleur invalide\n");
		free_all_exit(game, EXIT_FAILURE, 0);
	}
	result = ft_strdup(str);
	if (!result)
	{
		ft_printf("Erreur : allocation mémoire échouée\n");
		free_all_exit(game, EXIT_FAILURE, 0);
	}
	return (result);
}
