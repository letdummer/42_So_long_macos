#include "../includes/so_long.h"

void	ft_move_player(t_game *game, int direction)
{
	int	aux_x;
	int	aux_y;

	aux_x = game->map.player_pos_x;
	aux_y = game->map.player_pos_y;
	game->images.last_direction = direction;
	if (direction == KEY_W || direction == KEY_UP)
		aux_y += -1;
	else if (direction == KEY_A || direction == KEY_LEFT)
		aux_x += -1;
	else if (direction == KEY_S || direction == KEY_DOWN)
		aux_y += 1;
	else if (direction == KEY_D || direction == KEY_RIGHT)
		aux_x += 1;
	if (ft_validate_move(aux_x, aux_y, game))
	{
        game->map.grid[game->map.player_pos_y][game->map.player_pos_x] = MAP_FLOOR;
		ft_update_grid(game, game->map.player_pos_x, game->map.player_pos_y);
		game->map.player_pos_x = aux_x;
		game->map.player_pos_y = aux_y;
		game->map.grid[aux_y][aux_x] = MAP_PLAYER;
		ft_update_grid(game, aux_x, aux_y);
		game->images.step_count++;
        game->moves++;
		ft_render_hud(game);
	}
}

int	ft_validate_move(int aux_x, int aux_y, t_game *game)
{
	int i;
	int j;

    if (aux_y < 0 || aux_x < 0 || aux_y >= game->map.height || aux_x >= game->map.width)
        return (0);
	if (game->map.grid[aux_y][aux_x] == MAP_WALL)
		return (0);
	else if (game->map.grid[aux_y][aux_x] == MAP_FLOOR)
		return (1);
	else if (game->map.grid[aux_y][aux_x] == MAP_COLLECT)
	{	
		game->collected_items++;
		if (game->collected_items == game->map.collectibles)
		{
			i = 0;
			while (i < game->map.height)
			{
				j = 0;
				while (j < game->map.width)
				{
					if (game->map.grid[i][j] == MAP_EXIT)
						ft_update_grid(game,  j, i);
					j++; 
				}
				i++;
			}
		}
		return (1);
	}
	else if (game->map.grid[aux_y][aux_x] == MAP_EXIT)
	{
		if (game->collected_items == game->map.collectibles)
		{
			ft_printf("WIN!\n");
			sleep(1);
			handle_close(game);
		}
		return (0);
	}
	return (0);
}



