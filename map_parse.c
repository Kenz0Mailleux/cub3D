/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:21:08 by kenzo             #+#    #+#             */
/*   Updated: 2024/11/28 20:03:59 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
// Fonction pour allouer la carte
#include "cub3D.h"

// Fonction chatgpt pour allouer la carte
int **allocate_map(int width, int height)
	{
	int **map;
	int i;

	map = (int **)malloc(sizeof(int *) * height);
	if (!map)
	{
		perror("Erreur d'allocation de la carte");
		exit(EXIT_FAILURE);
	}

	i = 0;
	while (i < height)
	{
		map[i] = (int *)malloc(sizeof(int) * width);
		if (!map[i])
		{
			perror("Erreur d'allocation d'une ligne de la carte");
			exit(EXIT_FAILURE);
		}
		i++;
	}

	return map;
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


	// fct chatgpt en attendant de faire la mienne
t_map *parse_map(const char *filename) 
{
	FILE *file = fopen(filename, "r");
	if (!file) {
		perror("Erreur d'ouverture du fichier");
		exit(EXIT_FAILURE);
	}

	t_map *map = malloc(sizeof(t_map));
	if (!map) {
		perror("Erreur d'allocation de la structure de carte");
		exit(EXIT_FAILURE);
	}

	char line[1024];
	int width = 0, height = 0;

	// Lire les lignes du fichier pour déterminer la taille de la carte
	while (fgets(line, sizeof(line), file)) {
		if (line[0] == '1' || line[0] == '0') {  // Trouver la première ligne de la carte
			int len = strlen(line);
			if (len > width) width = len; // Calculer la largeur maximale de la carte
			height++;
		}
	}

	// Rewind pour relire le fichier depuis le début
	rewind(file);

	// Allouer la carte avec la taille calculée
	map->data = allocate_map(width, height);
	map->width = width;
	map->height = height;

	// Lire à nouveau le fichier et remplir la carte
	int y = 0;
	while (fgets(line, sizeof(line), file)) {
		if (line[0] == '1' || line[0] == '0') {  // Ligne de la carte
			for (int x = 0; x < width; x++) {
				if (line[x] == '1') {
					map->data[y][x] = 1;  // Mur
				} else if (line[x] == '0') {
					map->data[y][x] = 0;  // Espace vide
				} else {
					map->data[y][x] = 0;  // Par défaut espace vide
				}
			}
			y++;
		}
	}

	fclose(file);
	return map;
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
			printf("%d ", map->data[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}
