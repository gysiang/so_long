/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:55:19 by gyong-si          #+#    #+#             */
/*   Updated: 2023/10/30 10:16:07 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef MAX_FILES_OPEN
#  define MAX_FILES_OPEN 10
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <stddef.h>
# include <string.h>

char	*get_next_line(int fd);
char	*ft_strchr(const char	*str, const int c);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strdup(const char *s);
char	*check_null(const char *s);
size_t	ft_strlen(const char *str);
#endif
