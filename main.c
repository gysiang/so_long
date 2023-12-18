/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:19:24 by gyong-si          #+#    #+#             */
/*   Updated: 2023/12/18 16:28:27 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_utils.h"

void	open_map(const char *filename, const char **array)
{
	int	fd;
	char	*line;
	int	i;

	i = 0;
	fd = open(filename, O_RDONLY, 0666);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		array[i] = ft_strdup(line);
		printf("%s",array[i]);
		free(line);
		i++;
		if (i == MAX_ROWS)
			break;
	}
	close(fd);
}

int checkBorder(const char **map) 
{
    int i = 0;
	int	len = ft_strlen(map[0]) - 2;
	int	rows = 0;

	while (map[rows] != NULL)
		rows++;
    while (map[0][i] != '\n') 
	{
		if (map[0][i] != '1' || map[rows -1][i] != '1')
			return (0);
        i++;
    }
	i = 0;
	while (map[i])
	{
		if (map[i][0] != '1' || map[i][len] != '1')
			return (0);
		i++;
	}
    return (1);
}

int	checkRect(const char **map)
{
	int	rows;
	int	columns;

	rows = 0;
	columns = 0;
	while (map[rows] != NULL)
		rows++;
	while (map[0][columns] != '\n')
		columns++;
	printf("columns: %d\n", columns);
	printf("rows: %d\n", rows); 
	if (columns > rows)
		return (1);
	return (0);
}

int	checkAccess(const char **map, const int x, const int y)
{
	if (map[x - 1][y] == '0' || map[x + 1][y] == '0' 
			|| map[x][y - 1] == '0' || map[x][y + 1] == '0')
	{
		return (1);
	}
	return (0);
}

int	checkValidMap(const char **map)
{
	int	coins = 0;
	int	map_exit = 0;
	int	player = 0;
	int	rows = 0;
	int	i;

	while (map[rows] != NULL)
	{
		i = 0;
		while (map[rows][i] != '\n')
		{
			if (map[rows][i] == 'C')
			{
				if (checkAccess(map, rows, i))
					coins++;
				else
					break;
			}
			if (map[rows][i] == 'E')
			{
				if (checkAccess (map, rows, i))
					map_exit++;
				else
					break;
			}
			if (map[rows][i] == 'P')
				player++;
			i++;
		}
		rows++;
	}
	//printf("coins: %d\n", coins);
	//printf("player: %d\n", player);
	//printf("map_exit: %d\n", map_exit);
	if (map_exit == 1 && player == 1 && coins >= 1)
		//printf("This map is valid\n");
		return (1);
	else
		//printf("This map is not valid\n");
		return (0);
}
/**
int	main(int ac, char **av)
{
	const char	**map;

	if (ac == 2)
	{
		map = malloc(sizeof(char *) * (MAX_ROWS + 1));
		open_map(av[1], map);
		checkValidMap(map);
	}
} **/

void	*load_image(char *path, void *mlx_ptr)
{
	int	height;
	int	width;

	return (mlx_xpm_file_to_image(mlx_ptr, path, &width, &height));
}

void	*map_images(char c, void	*mlx_ptr)
{
	char	*image_path;

	if (c == '0')
		image_path = "assets/sprites/grass.xpm";
	if (c == '1')
		image_path = "assets/sprites/tree.xpm";
	if (c == 'C')
		image_path = "assets/sprites/pokeball.xpm";
	if (c == 'E')
		image_path = "assets/sprites/door.xpm";
	if (c == 'P')
		image_path = "assets/sprites/front_character.xpm";
	return (load_image(image_path, mlx_ptr));
}

void	render_map(const char **map, void *mlx_ptr, void *win_ptr)
{
	int	row = 0;
	int	i;
	void	*image;

	while (map[row] != NULL)
	{
		i = 0;
		while (map[row][i] != '\n')
		{
			image = map_images(map[row][i], mlx_ptr);
			if (image != NULL)
				mlx_put_image_to_window(mlx_ptr, win_ptr, image, i * TILE_SIZE, row * TILE_SIZE);
			i++;
		}
		row++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;
	int	width, height;
	const char	**map;

	if (ac == 2)
	{
		checkfiletype(av[1]);
		map = malloc(sizeof(char *) * (MAX_ROWS + 1));
		open_map(av[1], map);
		data.mlx_ptr = mlx_init();
		if (!data.mlx_ptr)
			return (1);
		data.win_ptr = mlx_new_window(data.mlx_ptr, 1920, 1080, "This is a window");
		if (!data.win_ptr)
			return (free(data.mlx_ptr), 1);
		mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &data);
		mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &data);
		//data.img_ptr = mlx_xpm_file_to_image(data.mlx_ptr, FLOOR_XPM, &width, &height);
		//mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img_ptr, IMG_WIDTH, IMG_HEIGHT);
		render_map(map, data.mlx_ptr, data.win_ptr);
		mlx_loop(data.mlx_ptr);
	}
	return (0);
}
