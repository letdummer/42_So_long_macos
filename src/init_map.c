#include "../includes/so_long.h"

int ft_validate_game_init(t_game *game)
{
    if (!game || game->map.player_pos_x == -1 || game->map.player_pos_y == -1)
        return (ft_printf("Debug: Invalid game structure\n"), 1);
    
    ft_printf("Debug: Starting MLX initialization\n");
    game->mlx_connection = mlx_init();
    if (!game->mlx_connection)
        return (ft_printf("Debug: MLX initialization failed\n"), 1);
    
    ft_printf("Debug: Starting window initialization\n");
    if (ft_init_wind(game) != 0)
    {
        ft_printf("Debug: Window initialization failed\n");
        ft_cleanup(game);
        return (1);
    }
    
    ft_printf("Debug: Game initialization complete\n");
    return (0);
}
/* 
int	ft_map_init(t_game *game, char *map_path)
{
    if (!game)
        return (ft_printf("Debug: Invalid game pointer\n"), 1);
        
    // Validate map structure initialization
    if (game->map.grid != NULL)
        return (ft_printf("Debug: Map already initialized\n"), 1);
        
    if (ft_get_map_dimensions(game, map_path) != 0)
        return (1);
	if (ft_allocate_map_memory(game) != 0)
		return (1);
	if (ft_fill_map_content(game, map_path) != 0)
	{
		ft_cleanup(game);
		return (1);
	}
	return (0);
}
int ft_get_map_dimensions(t_game *game, char *map_path)
{
    int     fd;
    char    *line;
    size_t  height;
    size_t  width;

    ft_printf("Debug: Starting map dimensions check\n");
    
    // Input validation
    if (!game || !map_path)
        return (ft_printf("Debug: Invalid parameters\n"), 1);
    
    // Open file
    fd = open(map_path, O_RDONLY);
    ft_printf("Debug: File descriptor: %d\n", fd);
    if (fd < 0)
        return (ft_printf("Debug: Failed to open map file\n"), 1);

		ft_printf("Debug: About to call get_next_line\n");
		void *gnl_ptr = (void*)get_next_line;  // Check if function pointer is NULL
		ft_printf("Debug: GNL function pointer: %p\n", gnl_ptr);

    // Read first line to get width
    ft_printf("Debug: Reading first line\n");
    line = get_next_line(fd);
	while (line)
	{
		printf("line: %s", line);
		free(line);
		line = get_next_line(fd);
	}
    // Calculate width (excluding newline)
    width = ft_strlen(line);
    if (line[width - 1] == '\n')
        width--;
    free(line);

    // Count lines for height
    height = 1;
    while ((line = get_next_line(fd)))
    {
        size_t line_width = ft_strlen(line);
        if (line[line_width - 1] == '\n')
            line_width--;
            
        // Check if all lines have same width
        if (line_width != width)
        {
            free(line);
            close(fd);
            return (ft_printf("Debug: Inconsistent line width\n"), 1);
        }
        free(line);
        height++;
    }

    // Validate dimensions
    if (height < 3 || width < 3)
    {
        close(fd);
        return (ft_printf("Debug: Map too small (min 3x3)\n"), 1);
    }

    // Set dimensions in game struct
    game->map.width = width;
    game->map.height = height;
    
    ft_printf("Debug: Map dimensions: %zux%zu\n", width, height);
    close(fd);
    return (0);
}

int ft_fill_map_content(t_game *game, const char *map_path)
{
	int		fd;
	char	*str;
	int		i;

	if (!game || !map_path || !game->map.grid)
		return (1);
	i = 0;
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (1);
	while ((str = get_next_line(fd)) != NULL && i < game->map.height)
	{
		if ((ft_strlen(str) - 1) != (size_t)game->map.width)
		{
			free(str);
			return (close(fd), 1);
		}
		ft_strlcpy(game->map.grid[i], str, game->map.width + 1);
		free(str);
		i++;
	}
	close(fd);
	if (i != game->map.height)
		return (1);
	return (0);
}
 */

 int ft_map_init(t_game *game, char *map_path)
{
    char    **temp_map;
    size_t  height;
    size_t  width;

    if (!game)
        return (ft_printf("Debug: Invalid game pointer\n"), 1);
        
    if (game->map.grid != NULL)
        return (ft_printf("Debug: Map already initialized\n"), 1);
    
    // First read the entire map into a temporary array
    temp_map = ft_read_map_file(map_path, &height, &width);
    if (!temp_map)
        return (1);
    
    // Validate map dimensions and content
    if (ft_validate_map_content(temp_map, height, width) != 0)
    {
        ft_free_temp_map(temp_map);
        return (1);
    }
    
    // Set dimensions and allocate final map
    game->map.height = height;
    game->map.width = width;
    if (ft_allocate_map_memory(game) != 0)
    {
        ft_free_temp_map(temp_map);
        return (1);
    }
    
    // Copy validated map to game structure
    if (ft_copy_map_to_game(game, temp_map) != 0)
    {
        ft_free_temp_map(temp_map);
        ft_cleanup(game);
        return (1);
    }
    
    ft_free_temp_map(temp_map);
    return (0);
}

int ft_allocate_map_memory(t_game *game)
{
	int i;

	if (!game || game->map.height <= 0 || game->map.width <= 0)
		return (1);
	i = 0;
	game->map.grid = ft_calloc(game->map.height + 1, sizeof(char *));
	if (!game->map.grid)
		return (1);
		ft_printf("Debug: Memory allocated for map grid\n");

	while (i < game->map.height)
	{
		game->map.grid[i] = ft_calloc(game->map.width + 1, sizeof(char));
		if (!game->map.grid[i])
		{
			while (--i >= 0)
				free(game->map.grid[i]);
			free(game->map.grid);
			return (1);
		}
		i++;
	}
	ft_printf("Debug: Memory allocated for each row in map grid\n");

	return (0);
}
#include "../includes/so_long.h"

#include "../includes/so_long.h"

char **ft_read_map_file(char *map_path, size_t *height, size_t *width)
{
    int     fd;
    char    *line;
    char    **temp_map;
    size_t  i;

    *height = 0;
    *width = 0;
    fd = open(map_path, O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening map file");
        return (NULL);
    }
    ft_printf("Debug: File opened successfully\n");
    while ((line = get_next_line(fd)))
    {
        if (*height == 0)
        {
            *width = ft_strlen(line) - (line[ft_strlen(line) - 1] == '\n' ? 1 : 0);
             if (*width <= 0) {
                free(line);
                close(fd);
                ft_printf("Error: Invalid map width\n");
                return NULL;
            }
        }
        free(line);
        (*height)++;
    }
     if (*height == 0) {
        close(fd);
        ft_printf("Error: Map is empty\n");
        return NULL;
    }
    close(fd);
    ft_printf("Debug: Map dimensions: %zux%zu\n", *width, *height);
    temp_map = ft_calloc(*height + 1, sizeof(char *));
    if (!temp_map)
    {
        perror("Error allocating memory for map");
        return (NULL);
    }
    fd = open(map_path, O_RDONLY);
    if (fd < 0)
    {
        free(temp_map);
        perror("Error opening map file");
        return (NULL);
    }
    i = 0;
    while ((line = get_next_line(fd)) && i < *height)
    {
        temp_map[i] = ft_strdup(line);
        if (!temp_map[i]) {
            close(fd);
            ft_free_temp_map(temp_map);
            perror("Error allocating memory for line");
            return NULL;
        }
        free(line);
        i++;
    }
    close(fd);
    ft_printf("Debug: Map content read successfully\n");
    return (temp_map);
}


int ft_validate_map_content(char **map, size_t height, size_t width)
{
    size_t  i;
    size_t  j;
    int     player;
    int     exit;
    int     collect;

    if (height < 3 || width < 3)
        return (ft_printf("Error: Map too small\n"), 1);

    player = 0;
    exit = 0;
    collect = 0;

    // Check borders and count elements
    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                if (map[i][j] != '1')
                    return (ft_printf("Error: Map not closed\n"), 1);
            }
            if (map[i][j] == 'P')
                player++;
            else if (map[i][j] == 'E')
                exit++;
            else if (map[i][j] == 'C')
                collect++;
            else if (map[i][j] != '0' && map[i][j] != '1')
                return (ft_printf("Error: Invalid character in map\n"), 1);
            j++;
        }
        i++;
    }

    if (player != 1 || exit != 1 || collect < 1)
        return (ft_printf("Error: Invalid number of elements\n"), 1);

    return (0);
}

int ft_copy_map_to_game(t_game *game, char **temp_map)
{
    int i;

    i = 0;
    while (i < game->map.height)
    {
        ft_printf("Debug: Copying row %d\n", i);
        ft_strlcpy(game->map.grid[i], temp_map[i], game->map.width + 1);
        i++;
    }
    ft_printf("Debug: Map copied successfully\n");
    return (0);
}

void ft_free_temp_map(char **temp_map)
{
    int i;

    if (!temp_map)
        return;
    i = 0;
    while (temp_map[i])
    {
        free(temp_map[i]);
        i++;
    }
    free(temp_map);
}