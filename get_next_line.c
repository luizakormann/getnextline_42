/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:03:55 by lukorman          #+#    #+#             */
/*   Updated: 2024/11/26 20:26:20 by lukorman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_read_file	file[FD_O_LIMIT];

	if (fd > FD_O_LIMIT || fd < 0)
		return (NULL);
	if (file[fd].i == 0 || file[fd].i >= file[fd].rd)
	{
		file[fd].i = 0; // new reading. needs to reset i to 0
		while (file[fd].i < BUFFER_SIZE) // this loop will empy the .buf with \0 for each index position
		{ // to-do: check for other possibilities, such as the creation of a free_buf function
			file[fd].buf[file[fd].i] = '\0';
			file[fd].i++;
		}
		// renicialize everything to zero
		file[fd].i = 0;
		file[fd].len = 0;
		file[fd].i = 0;
		file[fd].read_chars = NULL;
		file[fd].rd = read(fd, file[fd].read_chars, BUFFER_SIZE);
		if (file[fd].rd == ERROR)
			return (free_buf(file->read_chars)); //to-do: understand better this return - especifically the argument to the free_buf ft

	}
}
