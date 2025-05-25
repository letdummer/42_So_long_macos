#include "../includes/so_long.h"

void	ft_move_player(t_game *game, int direction)
{
	int	pos_aux_x;
	int	pos_aux_y;

	pos_aux_x = game->map.player_pos_x;
	pos_aux_y = game->map.player_pos_y;
 
	ft_printf("\n\nCurrent position: [%d]", pos_aux_y);
	ft_printf("[%d]\n", pos_aux_x);

	if (direction == KEY_W)
		pos_aux_y += -1;
	else if (direction == KEY_A)
		pos_aux_x += -1;
	else if (direction == KEY_S)
		pos_aux_y += 1;
	else if (direction == KEY_D)
		pos_aux_x += 1;
	
		ft_printf("Attempting to move to: [%d]", pos_aux_y);
		ft_printf("[%d]\n\n", pos_aux_x);

	if (ft_validate_move(pos_aux_x, pos_aux_y, game))
	{
		// Clear old position
		ft_printf("[2] Current map element: %c\n", game->map.grid[pos_aux_y][pos_aux_x]);

        game->map.grid[game->map.player_pos_y][game->map.player_pos_x] = MAP_FLOOR;
        
		game->map.player_pos_x = pos_aux_x;
		game->map.player_pos_y = pos_aux_y;
		
		game->map.grid[pos_aux_y][pos_aux_x] = MAP_PLAYER;
        
        game->moves++;
        ft_printf("Moviment valid!\tMoves: %d\n", game->moves);
	}

}

int	ft_validate_move(int pos_aux_x, int pos_aux_y, t_game *game)
{
	    // Add boundary checks first
    if (pos_aux_y < 0 || pos_aux_x < 0 || 
        pos_aux_y >= game->map.height || pos_aux_x >= game->map.width)
        return 0;

    // Debug prints to help track the issue
    ft_printf("Trying to move to position [%d]", pos_aux_y);
    ft_printf("[%d]\n",  pos_aux_x);
    ft_printf("[1] Current map element: %c\n", game->map.grid[pos_aux_y][pos_aux_x]);

	if (game->map.grid[pos_aux_y][pos_aux_x] == MAP_WALL)
		return 0;
	else if (game->map.grid[pos_aux_y][pos_aux_x] == MAP_FLOOR)
		return 1;
	else if (game->map.grid[pos_aux_y][pos_aux_x] == MAP_COLLECT)
	{	
		game->collected_items++;
		return 1;
	}
	else if (game->map.grid[pos_aux_y][pos_aux_x] == MAP_EXIT) // falta verificar se tudo ja foi coletado
		return 1;
	return 0;
}