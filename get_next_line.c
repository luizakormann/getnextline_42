/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:03:55 by lukorman          #+#    #+#             */
/*   Updated: 2024/12/05 18:07:34 by lukorman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*ptr;

	if (!s1 && !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ptr = (char *)malloc(len1 + len2 + 1);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s1, len1);
	ft_memcpy(ptr + len1, s2, len2);
	ptr[len1 + len2] = '\0';
	return (ptr);
}

static int	read_and_process(int fd, char **remainder)
{
	char	*buffer;
	char	*temp;
	ssize_t	bytes_read;

	if (!remainder) 
        return (-1);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(buffer);
		return (-1);
	}
	if (bytes_read == 0)
    {
        free(buffer);
        return (0);
    }
	buffer[bytes_read] = '\0';
	if (!*remainder)
		*remainder = ft_strdup("");

	temp = ft_strjoin(*remainder, buffer);
	free(buffer);
	if (!temp)
	{
		free(*remainder);
		*remainder = NULL;
		return (-1);
	}

	free(*remainder);
	*remainder = temp;
	return (bytes_read);
}

static char	*extract_line(char **remainder)
{
	char	*newline;
	char	*line;
	char	*temp;

	if (!remainder || !*remainder || **remainder == '\0')
		return (NULL);
	newline = NULL;
	temp = NULL;
	newline = ft_strchr(*remainder, '\n');
	if (newline)
	{
		line = ft_substr(*remainder, 0, newline - *remainder + 1);
		temp = ft_strdup(newline + 1);
		if (!line || !temp)
		{
			free(line);
			free(temp);
			return (NULL);
		}
		free(*remainder);
		*remainder = temp;
		return (line);
	}
	line = ft_strdup(*remainder);
	free(*remainder);
	*remainder = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*remainder[1024];
	char		*line;
	int			read_result;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	while (1)
	{
		if (remainder[fd] && ft_strchr(remainder[fd], '\n'))
			break ;
		read_result = read_and_process(fd, &remainder[fd]);
		if (read_result < 0)
		{
			free(remainder[fd]);
			remainder[fd] = NULL;
			return (NULL);
		}
		if (read_result == 0)
			break ;
	}

	line = extract_line(&remainder[fd]);
	if (!line)
	{
		free(remainder[fd]);
		remainder[fd] = NULL;
	}

	return (line);
}