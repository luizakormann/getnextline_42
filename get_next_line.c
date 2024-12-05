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

char	*read_line_from_file(int fd, t_read_file *file)
{
	t_buf_mngr	*rd_chrs;
	int			chr;
	size_t		line_len;

	rd_chrs = NULL;
	file->fd = fd;
	chr = read_next_char(file);
	if (chr == 0)
		return (NULL);
	line_len = 0;
	while (chr > 0)
	{
		add_node(&rd_chrs, (char)chr);
		line_len++;
		if (chr == '\n')
			break ;
		chr = read_next_char(file);
		if (chr == -1)
			return (free_list(&rd_chrs));
	}
	if (!rd_chrs)
		return (NULL);
	free_list(&rd_chrs);
	return (write_str(rd_chrs, line_len));
}

char	*get_next_line(int fd)
{
	static t_read_file	file[FD_O_LIMIT];

	if (fd < 0 || fd >= FD_O_LIMIT || BUFFER_SIZE <= 0)
		return (NULL);
	file[fd].fd = fd;
	return (read_line_from_file(fd, &file[fd]));
}
