#include "../includes/so_long.h"

void	ft_move_player(t_game *game, int direction)
{
	int	pos_aux_x;
	int	pos_aux_y;

	pos_aux_x = game->map.player_pos_x;
	pos_aux_y = game->map.player_pos_y;
	game->images.last_direction = direction;
	if (direction == KEY_W || direction == KEY_UP)
		pos_aux_y += -1;
	else if (direction == KEY_A || direction == KEY_LEFT)
		pos_aux_x += -1;
	else if (direction == KEY_S || direction == KEY_DOWN)
		pos_aux_y += 1;
	else if (direction == KEY_D || direction == KEY_RIGHT)
		pos_aux_x += 1;
	if (ft_validate_move(pos_aux_x, pos_aux_y, game))
	{
        game->map.grid[game->map.player_pos_y][game->map.player_pos_x] = MAP_FLOOR;
		ft_update_grid(game, game->map.player_pos_x, game->map.player_pos_y);
		game->map.player_pos_x = pos_aux_x;
		game->map.player_pos_y = pos_aux_y;
		game->map.grid[pos_aux_y][pos_aux_x] = MAP_PLAYER;
		ft_update_grid(game, pos_aux_x, pos_aux_y);
		game->images.step_count++;
        game->moves++;
		ft_display_moves(game);
	}
}

int	ft_validate_move(int pos_aux_x, int pos_aux_y, t_game *game)
{
    if (pos_aux_y < 0 || pos_aux_x < 0 || 
        pos_aux_y >= game->map.height || pos_aux_x >= game->map.width)
        return (0);

	if (game->map.grid[pos_aux_y][pos_aux_x] == MAP_WALL)
		return (0);
	else if (game->map.grid[pos_aux_y][pos_aux_x] == MAP_FLOOR)
		return (1);
	else if (game->map.grid[pos_aux_y][pos_aux_x] == MAP_COLLECT)
	{	
		game->collected_items++;
		return (1);
	}
	else if (game->map.grid[pos_aux_y][pos_aux_x] == MAP_EXIT) // falta verificar se tudo ja foi coletado
	{
		if (game->collected_items == game->map.collectibles)
		{
			ft_printf("WIN!\n");
			//adicionar uma imagem de 'vitoria'
			sleep(01);
			handle_close(game);
		}
		return (0);
	}
	return (0);
}



