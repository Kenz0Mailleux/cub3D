/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 01:38:13 by kenzo             #+#    #+#             */
/*   Updated: 2025/04/22 05:42:06 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'\
	|| c == '\v' || c == '\f' || c == '\r');
}

int	check_strings(char **array)
{
	int	i;
	int	j;

	i = 0;
	while (array[i] != NULL)
	{
		j = 0;
		while (array[i][j] != '\0')
		{
			if (!ft_isspace(array[i][j]))
			{
				return (i);
			}
			j++;
		}
		i++;
	}
	return (-1);
}

int	convert_to_hex_color(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_printf("Erreur : Valeur RGB invalide");
		exit(EXIT_FAILURE);
	}
	return ((r << 16) | (g << 8) | b);
}

void	print_map(t_map *map)
{
	int	y;
	int	x;

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

char	*ft_strncpy_cb(char *dest, char *src, int n)
{
	int	i;

	if (!dest || !src || n <= 0)
		return (NULL);
	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
