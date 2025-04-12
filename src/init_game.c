/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:41:43 by ldummer-          #+#    #+#             */
/*   Updated: 2025/04/11 20:29:28 by ldummer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* t_game	*ft_init_game(void)
{
	t_game	*game;

	game = (t_game *)ft_calloc(1, sizeof(t_game));
	if (!game)
		ft_error_message("Memory allocation failed for game structure.");
	return (game);
} */
static void init_map_values(t_map *map)
{
    // Initialize map structure with default values
    map->width = 0;
    map->height = 0;
    map->grid = NULL;
    map->walls = 0;
    map->floor = 0;
    map->collectibles = 0;
    map->exits = 0;
    map->player_pos_x = -1;
    map->player_pos_y = -1;
}

t_game *ft_init_game(void)
{
    t_game *game;
    
    ft_printf("Debug: Initializing game structure\n");
    game = (t_game *)ft_calloc(1, sizeof(t_game));
    if (!game)
        return (NULL);
    
    // Initialize map values using helper function
    init_map_values(&game->map);
    
    // Initialize game state values
    game->mlx_connection = NULL;
    game->mlx_wind = NULL;
    game->collected_items = 0;
    game->moves = 0;
    game->game_over = 0;
    game->win = 0;
    
    // Initialize image pointers to NULL
    game->images.wall = NULL;
    game->images.floor = NULL;
    game->images.collectible = NULL;
    game->images.exit = NULL;
    game->images.player = NULL;
    
    return (game);
}