#include "../includes/so_long.h"

t_game	*ft_init_game(void)
{
	t_game	*game;
	game = (t_game *)ft_calloc(1, sizeof(t_game));
	if (!game)
		ft_error_message("Memory allocation failed for game structure.");
	return (game);
}
/* 
void	ft_set_player_position(t_game *game)
{
	int y;
	int x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == MAP_PLAYER)
			{
				game->map.player_pos_x = x;
				game->map.player_pos_y = y;
				ft_printf("Player starting position: [%d][%d]\n", y, x);
				return;
			}
			x++;
		}
		y++;
	}
} */