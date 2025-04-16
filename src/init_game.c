#include "../includes/so_long.h"

t_game	*ft_init_game(void)
{
	t_game	*game;
	game = (t_game *)ft_calloc(1, sizeof(t_game));
	if (!game)
		ft_error_message("Memory allocation failed for game structure.");
	return (game);
}