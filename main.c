/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:19:24 by gyong-si          #+#    #+#             */
/*   Updated: 2023/12/15 15:04:14 by gyong-si         ###   ########.fr       */
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

int checkfirstandlastline(const char **map, const int count) 
{
    int i = 0;

    while (map[0][i] != '\n') 
	{
		if (map[0][i] != 49)
			return (0);
        i++;
    }
	i = 0;
	while (map[count-1][i] != '\n')
	{
		if (map[0][i] != 49)
			return (0);
		i++;
	}
    return (1);
}

int	main(int ac, char **av)
{
	const char	**map;
	int	i = 0;
	int	no_of_lines = 0;

	if (ac == 2)
	{
		map = malloc(sizeof(char *) * (MAX_ROWS + 1));
		open_map(av[1], map);
		while (map[i] != NULL)
		{
			no_of_lines++;
			i++;
		}
		// check if first line and last line is all 1s
		int	checkresult = checkfirstandlastline(map, no_of_lines);
		printf("%d", checkresult);
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
