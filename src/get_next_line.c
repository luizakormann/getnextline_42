/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:03:55 by lukorman          #+#    #+#             */
/*   Updated: 2025/03/03 21:23:29 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

static int	init_file_buffer(t_read_file *file, int fd)
{
	file->fd = fd;
	file->i = 0;
	file->rd = 0;
	return (1);
}

static void	cleanup_file_buffer(t_read_file *file)
{
	free_static_buffer(file);
	file->i = 0;
	file->rd = 0;
}

char	*get_next_line(int fd)
{
	static t_read_file	file[1024];
	char				*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (file[fd].buf == NULL)
	{
		file[fd].buf = malloc(BUFFER_SIZE + 1);
		if (!file[fd].buf)
			return (NULL);
		if (!init_file_buffer(&file[fd], fd))
		{
			cleanup_file_buffer(&file[fd]);
			return (NULL);
		}
	}
	line = read_line_from_file(&file[fd]);
	if (!line)
	{
		free_static_buffer(&file[fd]);
		return (NULL);
	}
	if (line[0] == '\0')
	{
		free(line);
		free_static_buffer(&file[fd]);
		return (NULL);
	}
	if (file[fd].rd <= 0)
		free_static_buffer(&file[fd]);
	return (line);
}
