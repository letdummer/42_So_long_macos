/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:17:23 by ldummer-          #+#    #+#             */
/*   Updated: 2025/05/30 11:24:22 by ldummer-         ###   ########.fr       */
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

# define TILE_SIZE 64
# define WIND_WIDTH 1920
# define WIND_HEIGHT 1080

// COLORS
# define RED "\033[0;91m"
# define GREEN "\033[0;92m"
# define END_COLOR "\033[0;39m"

// Key codes for Mac
# define KEY_ESC	53
# define KEY_W		13
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2

# define KEY_UP			126
# define KEY_LEFT		123
# define KEY_RIGHT		124
# define KEY_DOWN		125

// key codes for linux?
//# define KEY_ESC  			65307
//# define KEY_W				119
//# define KEY_A				97
//# define KEY_S				115
//# define KEY_D				100

//# define KEY_UP  			65362
//# define KEY_LEFT  			65361
//# define KEY_RIGHT 			65363
//# define KEY_DOWN  			65364

//# define KEY_Q				113

// map element definition
# define MAP_WALL		'1'
# define MAP_FLOOR		'0'
# define MAP_COLLECT	'C'
# define MAP_EXIT		'E'
# define MAP_PLAYER		'P'

# define WALL_TOP_LEFT "assets/walls/tile_0_0.xpm"
# define WALL_TOP_RIGHT "assets/walls/tile_0_2.xpm"
# define WALL_BOTTOM_LEFT "assets/walls/tile_2_0.xpm"
# define WALL_BOTTOM_RIGHT "assets/walls/tile_2_2.xpm"
# define WALL_LEFT "assets/walls/tile_1_0.xpm"
# define WALL_RIGHT "assets/walls/tile_1_2.xpm"
# define WALL_TOP "assets/walls/tile_0_1.xpm"
# define WALL_BOTTOM "assets/walls/tile_2_1.xpm"
# define WALL "assets/walls/tile_1_1.xpm"

//	STRUCTURES
typedef struct	s_img
{
	void	*wall;
	void	*floor;
	void	*collectible;
	void	*exit;
	void	*player;
	int		width; 
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct	s_map
{
	char	**grid;
	int		width;
	int		height;
	int		walls;
	int		floor;
	int		collectibles;
	int		player;
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
void	gnl_clear(int fd);

// INIT_GAME.C
t_game	*ft_init_game(void);
//void	ft_set_player_position(t_game *game);

// INIT_MAP.C
void	ft_map_init(t_game *game, char *map_path);
void	ft_get_map_dimensions(t_game *game, char *map_path);
int		ft_count_lines(char *map_path);
void	ft_allocate_map_memory(t_game *game);
void	ft_fill_map_content(t_game *game, char *map_path);

// INIT_WINDOW.C
void	ft_init_wind(t_game *game);
int	handle_input(int key, t_game *game);
int	handle_close(t_game *game);

// MOVIMENTS.C
void	ft_move_player(t_game *game, int direction);
int		ft_validate_move(int pos_aux_x, int pos_aux_y, t_game *game);

// RENDER_IMAGES.C
void	ft_map_images(t_game *game);
void	ft_free_images(t_game *game);
void	ft_update_grid(t_game *game, int x, int y);
void	ft_display_moves(t_game *game);
void	ft_render_images(t_game *game);
char    *ft_walls_tiles(t_game *game, int x, int y);

// VALIDATE_MAP.C
void	ft_validate_map_extension(char *file);
void	ft_validate_map_content(t_game *game);
void	ft_check_line_content(char *str, int y, t_game *game);


#endif