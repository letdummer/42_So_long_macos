/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:17:23 by ldummer-          #+#    #+#             */
/*   Updated: 2025/04/14 17:13:51 by ldummer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

// LIBRARIES
#include "../minilibx-linux/mlx.h"
#include "../libft/libft/libft.h"
#include "../libft/ft_printf/libftprintf.h"
#include "../libft/get_next_line/get_next_line.h"

//#include <X11/keysym.h>				//descomentar para usar no linux
#include <Carbon/Carbon.h>			// Include for event handling on macOS

# define TILE_SIZE 32
# define WIND_WIDTH 800
# define WIND_HEIGHT 600

// COLORS
# define RED "\033[0;91m"
# define GREEN "\033[0;92m"
# define END_COLOR "\033[0;39m"

// Key codes for Mac
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2

// map element definition
# define MAP_WALL       '1'
# define MAP_FLOOR      '0'
# define MAP_COLLECT    'C'
# define MAP_EXIT       'E'
# define MAP_PLAYER     'P'

//	STRUCTURES
typedef struct	s_img
{
	void	*wall;
	void	*floor;
	void	*collectible;
	void	*exit;
	void	*player;
	int	 	width; 
	int	 	height;
	int	 	bits_per_pixel;
	int	 	line_length;
	int	 	endian;
}	t_img;

typedef struct	s_map
{
	char	**grid;
	int		width;
	int		height;
	int		walls;
	int		floor;
	int		collectibles;
	int		exits;
	int		player_pos_x;
	int		player_pos_y;
}	t_map;

typedef struct s_game
{
	void	*mlx_connection;
	void	*mlx_wind;
	t_map	map;
	t_img	images;
	int		collected_items;
	int		moves;
	int		game_over;
	int		win;
}	t_game;

// HANDLE_ERRORS.C
void	ft_error_message(char *message);

// INIT_GAME.C
t_game	*ft_init_game(void);


// INIT_WINDOW.C
void	ft_init_wind(t_game *game);
int	handle_input(int key, t_game *game);

// INIT_MAP.C
void	ft_map_init(t_game *game, char *map_path);
void	ft_get_map_dimensions(t_game *game, char *map_path);
int	ft_count_lines(char *map_path);
void ft_allocate_map_memory(t_game *game);
void ft_fill_map_content(t_game *game, char *map_path);

// RENDER_IMAGES.C
void	ft_render_images(t_game *game);
void	ft_free_images(t_game *game);

// VALIDATE_MAP.C
void	ft_validate_map_extension(char *file);





#endif