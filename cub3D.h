/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:00:08 by kenzo             #+#    #+#             */
/*   Updated: 2025/04/27 22:30:03 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "minilibx/mlx.h"
# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <string.h>

# define KEY_ESCAPE 65307
# define KEY_Z 122
# define KEY_Q 113
# define KEY_S 115
# define KEY_D 100
# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05
# define MAP_WIDTH 16
# define MAP_HEIGHT 6

typedef struct s_dir_parse	t_dir_parse;

typedef struct s_fill
{
	char	*buffer;
	int		bpp;
	int		line_size;
	int		endian;
}	t_fill;

typedef struct s_image
{
	void	*img_ptr;
	char	*path;
	int		found;
	int		*data;
	int		bpp;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_map
{
	int		**data;
	int		width;
	int		height;
	int		ground_color;
	int		ceiling_color;
	t_image	image[6];
}	t_map;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	int			initialised;
}	t_player;

typedef struct s_raycast
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		texture_x;
	int		texture_y;
	double	wall_x;
	int		tex_width;
	int		tex_height;
	char	*texture_data;
	int		color;
	int		*buffer;
	void	*img;
	int		*data;
}	t_raycast;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_image		images[6];
	int			bpp;
	t_player	player;
	int			map_width;
	int			map_height;
	int			player_x;
	int			player_y;
	int			player_found;
	t_map		*map;
	t_dir_parse	*parse;
}	t_game;

typedef struct s_dir_parse
{
	t_map	*map;
	t_game	*game;
}	t_dir_parse;

void	print_map(t_map *map);
void	test_images(t_game *mlx, int width, int height);
void	draw_scene(t_game *game);
void	raycast_calcul(t_game *game);
int		handle_keypress(int keycode, t_game *game);
t_map	*parse_map(char *filename, t_game *game);
t_game	*init_game(char *path, int width, int height, char *title);
void	free_map(int **map, int height);
void	free_all_exit(t_game *game, int succes, int free_mlx);
void	calculate_wall_distance(t_game *game, t_raycast *rc);
void	render_wall_slice(t_game *game, t_raycast *rc, int *buffer, int x);
void	render_to_window(t_game *game, int *buffer);
void	check_map_closed(t_game *game);
char	*find_path_textures_in_file(char *str, t_game *game);
int		parse_color( t_game *game, const char *str);
char	*find_path_color_in_file(char *str, t_game *game);
void	parse_and_validate_map(int **map, t_game *game);

/*map parse*/
int		found_all(t_map *map);
int		parse_texture_line(t_dir_parse *parse, char *line, \
int id, char *identifier);
void	parse_line(t_map *map, char *line, t_game *game);
int		ft_isempty_line(char *line);
int		ft_is_map_line(char *line);

/*map parse2*/
int		find_map_start(t_game *game, char **map_str, int i);
int		parse_file(t_map *map, char **map_str, t_game *game);
t_map	*init_map_struct(t_game *game);
void	calculate_map_dimensions(char **map_str, int *width,
			int *height, int start_index);

/*map parse3*/
void	fill_map_cell(t_game *game, t_map *map, char c, t_vector pos);
void	populate_map_data(char **map_str,
			t_map *map, t_game *game, int start_index);
void	verify_player_initialised(t_game *game);
t_map	*parse_map(char *filename, t_game *game);

/*map parse4*/
void	set_player_direction(t_game *game, char c);
void	set_player_direction_x(t_game *game, char c);
void	parse_player(t_game *game, t_map *map, t_vector pos, char c);

/*raycast*/
void	calcul_ray_dir(t_raycast *rc, t_game *game, int x);
void	calcul_move_dist(t_raycast *rc, t_game *game);
void	detect_collision(t_raycast *rc, t_game *game);
void	calcul_wall_dist(t_raycast *rc, t_game *game);
void	calcul_textre_x(t_raycast *rc, t_game *game);

/*raycast2*/
void	texture_wall(t_raycast *rc, t_game *game);
int		*allocate_buffer(t_game *game);
void	calculate_ray_for_pixel(t_raycast *rc, t_game *game, int x);
void	calculate_line_height(t_raycast *rc);
void	render_ceiling_and_floor(t_raycast *rc, t_game *game, int x);

/*raycast3*/
void	display_image(t_game *game, t_raycast *rc);
void	raycast_calcul(t_game *game);

/*map memory*/
void	init_map_image_path(t_map *map);
int		map_alloc_size(const char *filename);
int		**allocate_map(int width, int height, t_game *game);
void	free_map(int **map, int height);
char	**init_map_str(const char *filename, t_game *game);

/*utils*/
int		ft_isspace(char c);
int		check_strings(char **array);
int		convert_to_hex_color(t_game *game, int r, int g, int b);
char	*ft_strncpy_cb(char *dest, char *src, int n);
#endif
