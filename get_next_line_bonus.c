/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:45:50 by lukorman          #+#    #+#             */
/*   Updated: 2024/12/20 19:51:44 by lukorman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*build_line(t_buf_mngr **chrs_list, size_t line_len, int last_chr);

char	*read_line_from_file(t_read_file *file)
{
	t_buf_mngr	*chrs_list;
	int			chr;
	size_t		line_len;

	chrs_list = NULL;
	line_len = 0;
	while (1)
	{
		chr = read_next_char(file);
		if (chr <= 0)
			break ;
		add_node(&chrs_list, (char)chr);
		line_len++;
		if (chr == '\n')
			break ;
	}
	if (!chrs_list)
		return (NULL);
	return (build_line(&chrs_list, line_len, chr));
}

char	*build_line(t_buf_mngr **chrs_list, size_t line_len, int last_chr)
{
	char	*line;

	line = write_str(*chrs_list, line_len);
	free_list(chrs_list);
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
	if ((file[fd].rd == 0 && file[fd].i == 0) || file[fd].buf == NULL)
	{
		if (file[fd].buf != NULL)
			free(file[fd].buf);
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
