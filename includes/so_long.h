/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:17:23 by ldummer-          #+#    #+#             */
/*   Updated: 2025/03/23 21:46:45 by ldummer-         ###   ########.fr       */
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

//	MAIN
void	ft_initialize(t_game *game);
int	handle_input(int key, t_game *game);

// HANDLE_ERRORS
// Insert a message, do not need to add '\n'
void	ft_error_message(char *message);


//	RENDER_IMAGES
void	ft_render_images(t_game *game);
void	ft_free_images(t_game *game);

//	VALIDATE_MAP
void	ft_validate_map_extension(char *file);
void	ft_validate_map_size();

#endif