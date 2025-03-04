/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:36:35 by luiza             #+#    #+#             */
/*   Updated: 2025/03/03 23:53:22 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

char		*gnl_strchr(const char *s, int c);
static int	process_buffer(int fd, char *buffer, char **content);
static int	handle_read_error(char *buffer);

int	read_to_buffer(int fd, char **content)
{
	char	*buffer;
	int		bytes;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (-1);
	bytes = 1;
	while (!gnl_strchr(*content, '\n') && bytes > 0)
	{
		bytes = process_buffer(fd, buffer, content);
		if (bytes < 0)
			return (handle_read_error(buffer));
	}
	free(buffer);
	return (bytes);
}

char	*gnl_strchr(const char *s, int c)
{
	unsigned char	uc;

	if (!s)
		return (NULL);
	uc = (unsigned char)c;
	while (*s)
	{
		if (*(unsigned char *)s == uc)
			return ((char *)s);
		s++;
	}
	if (uc == '\0')
		return ((char *)s);
	return (NULL);
}

static int	process_buffer(int fd, char *buffer, char **content)
{
	int		bytes;
	char	*temp;

	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes < 0)
		return (-1);
	buffer[bytes] = '\0';
	temp = gnl_strjoin(*content, buffer);
	if (!temp)
		return (-1);
	*content = temp;
	return (bytes);
}

static int	handle_read_error(char *buffer)
{
	free(buffer);
	return (-1);
}
