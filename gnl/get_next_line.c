/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:30:47 by gyong-si          #+#    #+#             */
/*   Updated: 2023/10/30 10:12:40 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free(char *s)
{
	if (s != NULL)
		free(s);
	return (NULL);
}

static char	*extract_line(char *buffer)
{
	char	*line;
	int		i;
	int		len;

	if (buffer == NULL)
		return (NULL);
	i = 0;
	len = 0;
	while (buffer[len] && buffer[len] != '\n')
		len++;
	line = (char *)malloc(sizeof(char) * (len + 2));
	if (!line)
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static	char	*ft_nextchunk(char *buffer, size_t len)
{
	char	*res;
	int		i;
	size_t	buffer_len;
	size_t	len_to_copy;	

	if (!buffer || len <= 0)
		return (NULL);
	i = 0;
	buffer_len = ft_strlen(buffer);
	len_to_copy = buffer_len - len + 1;
	res = (char *)malloc(sizeof(char) * len_to_copy);
	if (!res)
		return (NULL);
	while (buffer[len + i] != '\0')
	{
		res[i] = buffer[len + i];
		i++;
	}
	res[i] = '\0';
	free(buffer);
	return (res);
}

char	*read_file(int fd, char *text)
{
	char	*res;
	char	*tmp;
	ssize_t	bytes_read;

	if (!text)
		return (ft_free(text));
	res = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!res)
		return (NULL);
	bytes_read = 1;
	while (bytes_read >= 1)
	{
		bytes_read = read(fd, res, BUFFER_SIZE);
		if (bytes_read < 0)
			break ;
		res[bytes_read] = 0;
		tmp = ft_strjoin(text, res);
		ft_free(text);
		text = tmp;
	}
	free(res);
	if (bytes_read < 0 || !text[0])
		return (ft_free(text));
	return (text);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!buffer)
	{
		buffer = (char *)malloc(sizeof(char) * 1);
		if (!buffer)
			return (NULL);
		*buffer = '\0';
	}
	buffer = read_file(fd, buffer);
	if (!buffer || buffer[0] == '\0')
		return (ft_free(buffer));
	line = extract_line(buffer);
	if (!line || line[0] == '\0')
	{
		ft_free(buffer);
		return (ft_free(line));
	}
	buffer = ft_nextchunk(buffer, ft_strlen(line));
	return (line);
}
/*
int	main(void)
{
	char	*line = NULL;
	int	fd;
	int	i = 0;

	fd = open("example.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (0);
		printf("LINE %d: %s",i++, line);
		free(line);
	}
	close(fd);
} */
