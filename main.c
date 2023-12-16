/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:19:24 by gyong-si          #+#    #+#             */
/*   Updated: 2023/12/16 10:59:14 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef	struct	s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
}				t_data;

int	on_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}

int	on_keypress(KeySym keysym, t_data *data)
{
	(void)data;

	char	*key = XKeysymToString(keysym);
	printf("Pressed key: %s\n", key);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}



void	checkfiletype(const char *filename)
{
	size_t	len = ft_strlen(filename);
	
	if (ft_strcmp(filename + len - 4, ".ber") == 0)
		printf("Yes. The file extension is .ber\n");
	else
		printf("No. The file extension is not .ber\n");
}

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
/**
int	checkfirstandlastcolumn(const char **map)
{
	int	len = ft_strlen(map[0]);
	int	i = 0;
	
	len -= 2;

	while (map[i])
	{
		if (map[i][0] != '1' || map[i][len] != '1')
			return (0);
		i++;
	}
	return (1);
} **/

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

void checkValidMap(const char **map)
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
	printf("coins: %d\n", coins);
	printf("player: %d\n", player);
	printf("map_exit: %d\n", map_exit);
	if (map_exit == 1 && player == 1 && coins >= 1)
		printf("This map is valid\n");
	else
		printf("This map is not valid\n");
}

int	main(int ac, char **av)
{
	const char	**map;

	if (ac == 2)
	{
		map = malloc(sizeof(char *) * (MAX_ROWS + 1));
		open_map(av[1], map);
		checkValidMap(map);
	}
}

/**
int	main(int ac, char **av)
{
	t_data	data;
	int	width, height;

	if (ac == 2)
	{
		checkfiletype(av[1]);
		data.mlx_ptr = mlx_init();
		if (!data.mlx_ptr)
			return (1);
		data.win_ptr = mlx_new_window(data.mlx_ptr, 600, 400, "This is a window");
		if (!data.win_ptr)
			return (free(data.mlx_ptr), 1);
		mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &data);
		mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &data);
		data.img_ptr = mlx_xpm_file_to_image(data.mlx_ptr, FLOOR_XPM, &width, &height);
		mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img_ptr, IMG_WIDTH, IMG_HEIGHT);
		mlx_loop(data.mlx_ptr);
	}
	return (0);
} **/
