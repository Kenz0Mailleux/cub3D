/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 01:40:38 by kenzo             #+#    #+#             */
/*   Updated: 2024/12/06 12:06:34 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"


int parse_color(const char *str)
{
	int r, g, b;
	int i = 0;

	while (str[i] && ft_isspace((unsigned char)str[i]))
		i++;
	r = ft_atoi(&str[i]);
	while (str[i] && ft_isdigit((unsigned char)str[i]))
		i++;
	if (str[i] != ',')
	{
		perror("Erreur : Format invalide");
		exit(EXIT_FAILURE);
	}
	i++;
	while (str[i] && ft_isspace((unsigned char)str[i]))
		i++;
	g = ft_atoi(&str[i]);
	while (str[i] && ft_isdigit((unsigned char)str[i]))
		i++;
	if (str[i] != ',')
	{
		perror("Erreur : Format invalide");
		exit(EXIT_FAILURE);
	}
	i++;
	while (str[i] && ft_isspace((unsigned char)str[i]))
		i++;
	b = ft_atoi(&str[i]);
	while (str[i] && ft_isdigit((unsigned char)str[i]))
		i++;
	while (str[i] && ft_isspace((unsigned char)str[i]))
		i++;
	if (str[i] != '\0')
	{
		perror("Erreur : Format invalide");
		exit(EXIT_FAILURE);
	}
	return convert_to_hex_color(r, g, b);
}