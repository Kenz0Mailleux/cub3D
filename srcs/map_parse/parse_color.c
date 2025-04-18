/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 01:40:38 by kenzo             #+#    #+#             */
/*   Updated: 2025/04/18 05:22:14 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	extract_color_value(const char *str, int *i)
{
	int	value;

	while (str[*i] && ft_isspace((unsigned char)str[*i]))
		(*i)++;
	value = ft_atoi(&str[*i]);
	while (str[*i] && ft_isdigit((unsigned char)str[*i]))
		(*i)++;
	return (value);
}

int	parse_color(const char *str)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 0;
	r = extract_color_value(str, &i);
	if (str[i++] != ',')
		return (perror("Erreur : Format invalide"), exit(EXIT_FAILURE), 0);
	g = extract_color_value(str, &i);
	if (str[i++] != ',')
		return (perror("Erreur : Format invalide"), exit(EXIT_FAILURE), 0);
	b = extract_color_value(str, &i);
	while (str[i] && ft_isspace((unsigned char)str[i]))
		i++;
	if (str[i] != '\0')
		return (perror("Erreur : Format invalide"), exit(EXIT_FAILURE), 0);
	return (convert_to_hex_color(r, g, b));
}
