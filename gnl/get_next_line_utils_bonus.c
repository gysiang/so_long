/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:11:22 by gyong-si          #+#    #+#             */
/*   Updated: 2023/10/29 16:11:42 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		total_len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	total_len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(sizeof(char) * (total_len + 1));
	if (!res)
		return (NULL);
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strchr(char *str, int c)
{
	while (*str != '\0' && *str != (char)c)
		++str;
	if (*str == (char)c)
		return ((char *)str);
	return (NULL);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}
