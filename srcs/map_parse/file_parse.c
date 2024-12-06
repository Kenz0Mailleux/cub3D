/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 01:49:58 by kenzo             #+#    #+#             */
/*   Updated: 2024/12/06 12:10:27 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

char *find_path_textures_in_file(char *str, t_game *game)
{
	int		i;
	int		j;
	char	*str_path;

	j = 0;
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
			
			str_path = malloc(sizeof(char) * (i - j + 1));
			str_path = ft_strncpy_gnl(str_path, &str[j], i - j);
			ft_printf(str_path);
			if (!str_path)
			{
				perror("erreur malloc");
				free_all_exit(game, EXIT_FAILURE);
			}
			while (str[i] && ft_isspace(str[i]))
			{
				ft_printf("%c", str[i]);
				if (str[i] == '\n')
					return (str_path);
				i++;
			}
			ft_printf("%c", str[i]);
			exit (1);
			free_all_exit(game, EXIT_FAILURE);
		}
	}
	return (NULL);
}

char *find_path_color_in_file(char *str, t_game *game)
{
	int 	i;
	char	*result;
	int 	start;

	i = 0;
	while (str[i] && ft_isspace((unsigned char)str[i]))
		i++;
	start = i;
	while (str[i] && ft_isdigit((unsigned char)str[i]))
		i++;
	if (start == i || str[i++] != ',')
	{
		perror("Erreur : format de couleur invalide");
		exit(1);
	}
	while (str[i] && ft_isspace((unsigned char)str[i]))
		i++;
	start = i;
	while (str[i] && ft_isdigit((unsigned char)str[i]))
		i++;
	if (start == i || str[i++] != ',')
	{
		perror("Erreur : format de couleur invalide");
		exit(1);
	}
	while (str[i] && ft_isspace((unsigned char)str[i]))
		i++;
	start = i;
	while (str[i] && ft_isdigit((unsigned char)str[i]))
		i++;
	while (str[i] && ft_isspace((unsigned char)str[i]))
		i++;
	if (start == i || str[i] != '\0')
	{
		perror("Erreur : format de couleur invalide");
		exit(1);
	}
	result = ft_strdup(str);
	if (!result)
	{
		perror("Erreur : allocation mémoire échouée");
		exit(1);
		free_all_exit(game, EXIT_FAILURE);
	}
	return (result);
}
