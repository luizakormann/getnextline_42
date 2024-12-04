/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:03:55 by lukorman          #+#    #+#             */
/*   Updated: 2024/12/04 00:07:12 by lukorman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_read_file	file[FD_O_LIMIT];
	t_buf_mngr			*read_chars;
	int					cur_c;
	size_t				line_len;
	char				*line;

	if (fd < 0 || fd >= FD_O_LIMIT || BUFFER_SIZE <= 0)
		return (NULL);
	file[fd].fd = fd;
	read_chars = NULL;
	cur_c = read_next_char(&file[fd]);
	if (cur_c == 0)
		return (NULL);
	line_len = 0;
	while (cur_c > 0)
	{
		add_node(&read_chars, (char)cur_c);
		line_len++;
		if (cur_c == '\n')
			break ;
		cur_c = read_next_char(&file[fd]);
		if (cur_c == -1)
		{
			free_list(&read_chars);
			return (NULL);
		}
	}
	if (!read_chars)
		return (NULL);
	line = write_str(read_chars, line_len);
	free_list(&read_chars);
	return (line);
}
