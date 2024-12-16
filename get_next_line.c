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

char	*build_line(t_buf_mngr **rd_chrs, size_t line_len, int last_chr);

char	*read_line_from_file(t_read_file *file)
{
	t_buf_mngr	*rd_chrs;
	int			chr;
	size_t		line_len;

	rd_chrs = NULL;
	line_len = 0;
	while (1)
	{
		chr = read_next_char(file);
		if (chr <= 0)
			break ;
		add_node(&rd_chrs, (char)chr);
		line_len++;
		if (chr == '\n')
			break ;
	}
	if (!rd_chrs)
		return (NULL);
	return (build_line(&rd_chrs, line_len, chr));
}

char	*build_line(t_buf_mngr **rd_chrs, size_t line_len, int last_chr)
{
	char	*line;

	line = write_str(*rd_chrs, line_len);
	free_list(rd_chrs);
	if (last_chr == -1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static t_read_file	file[1024];
	char				*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (file[fd].rd == 0 && file[fd].i == 0)
	{
		file[fd].fd = fd;
		file[fd].buf = malloc(BUFFER_SIZE);
		if (!file[fd].buf)
			return (NULL);
	}
	line = read_line_from_file(&file[fd]);
	if (!line)
	{
		free(file[fd].buf);
		file[fd].buf = NULL;
		file[fd].i = 0;
		file[fd].rd = 0;
	}
	return (line);
}
