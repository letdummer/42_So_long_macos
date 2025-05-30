#include "../includes/so_long.h"

t_game	*ft_init_game(void)
{
	t_game	*game;

	game = (t_game *)ft_calloc(1, sizeof(t_game));
	if (!game)
		return (NULL);
	game->mlx_connection = NULL;
	game->mlx_wind = NULL;
	game->images.floor = NULL;
	game->images.wall = NULL;
	game->images.collectible = NULL;
	game->images.exit = NULL;
	game->images.player_up_1 = NULL;
	game->images.player_up_2 = NULL;
	game->images.player_down_1 = NULL;
	game->images.player_down_2 = NULL;
	game->images.player_left_1 = NULL;
	game->images.player_left_2 = NULL;
	game->images.player_right_1 = NULL;
	game->images.player_right_2 = NULL;

	game->images.last_direction = KEY_D;
	game->images.step_count = 0;
	game->collected_items = 0;
	game->moves = 0;

	return (game);
}

void	ft_display_moves(t_game *game)
{
	char	*moves;
	char	*tmp;

	tmp = ft_itoa(game->moves);
	moves = ft_strjoin("MOVES: ", tmp);
	mlx_string_put(game->mlx_connection, game->mlx_wind,
		10, 20, 0xFFFFFF, moves);
	free (tmp);
	free (moves);
}