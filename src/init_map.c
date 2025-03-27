/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:10:49 by ldummer-          #+#    #+#             */
/*   Updated: 2025/03/26 18:33:56 by ldummer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_map_init(t_game *game, char *map_path)
{
	ft_get_map_dimensions(game, map_path);
	ft_allocate_map_memory(game);
	ft_fill_map_content(game, map_path);
}

void	ft_get_map_dimensions(t_game *game, const char *map_path)
{
	int		fd;
	char	*str;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		ft_error_message("Error while reading the map content.");
	if (!(str = get_next_line(fd)))
		ft_error_message("Empty file.");
	game->map.width = ft_strlen(str) - 1;
	game->map.height = ft_count_lines(map_path);
	if (game->map.height < 3)
		ft_error_message("Map is too small.");
	free(str);
	close(fd);
}

int	ft_count_lines(char *map_path)
{
	int		fd;
	int		line_length;
	char	*str;
	
	line_length = 0;
	fd = open(map_path, O_RDONLY);
	str = get_next_line(fd);
	while(str != NULL)
	{
		line_length++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return(line_length);
}

void ft_allocate_map_memory(t_game *game)
{
	int i;

	i = 0;
	game->map.grid = ft_calloc(game->map.height + 1, sizeof(char *));
	if (!game->map.grid)
		ft_error_message("Memory allocation failed");
	while (i < game->map.height)
	{
		game->map.grid[i] = ft_calloc(game->map.width + 1, sizeof(char));
		if (!game->map.grid[i])
		{
			// Free previously allocated memory
			while (--i >= 0)
				free(game->map.grid[i]);
			free(game->map.grid);
			ft_error_message("Memory allocation failed");
		}
		i++;
	}
}

void ft_fill_map_content(t_game *game, const char *map_path)
{
	int	 fd;
	char	*str;
	int	 i;

	i = 0;
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		ft_error_message("Error while reading the map content.");
	while ((str = get_next_line(fd)) != NULL && i < game->map.height)
	{
		if ((ft_strlen(str) - 1) != game->map.width)
			ft_error_message("Map must be rectangular.");
		ft_strlcpy(game->map.grid[i], str, game->map.width + 1);
		free(str);
		i++;
	}
	close(fd);
}