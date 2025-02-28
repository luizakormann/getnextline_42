/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:03:55 by lukorman          #+#    #+#             */
/*   Updated: 2025/02/28 13:00:56 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

char	*get_next_line(int fd)
{
	static t_read_file	file[1024];
	char				*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (file[fd].buf == NULL)
	{
		file[fd].fd = fd;
		file[fd].buf = malloc(BUFFER_SIZE + 1);
		if (!file[fd].buf)
			return (NULL);
		file[fd].i = 0;
		file[fd].rd = 0;
	}
	line = read_line_from_file(&file[fd]);
	if (!line)
	{
		free_static_buffer(&file[fd]);
		file[fd].i = 0;
		file[fd].rd = 0;
		return (NULL);
	}
	if (file[fd].rd <= 0)
	{
		free_static_buffer(&file[fd]);
		file[fd].i = 0;
		file[fd].rd = 0;
	}
	return (line);
}
