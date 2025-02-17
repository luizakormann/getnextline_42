/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_fts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:48:43 by luiza             #+#    #+#             */
/*   Updated: 2025/02/17 13:10:54 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

static int	init_build_line(t_buf_mngr **rd_chrs, char **line,
			size_t total_len)
{
	if (!rd_chrs || !*rd_chrs || total_len == 0)
	{
		free_list(rd_chrs);
		return (0);
	}
	*line = malloc(total_len + 1);
	if (!*line)
	{
		free_list(rd_chrs);
		return (0);
	}
	return (1);
}

static size_t	copy_content(char *line, size_t offset, t_buf_mngr *temp)
{
	size_t	content_len;

	content_len = 0;
	while (temp->content[content_len])
		content_len++;
	gnl_memcpy(line + offset, temp->content, content_len);
	return (content_len);
}

char	*process_read_line(t_buf_mngr *rd_chrs,
			size_t total_len, int last_chunk)
{
	if (!rd_chrs && last_chunk == -1)
		return (NULL);
	return (build_line(&rd_chrs, total_len, last_chunk));
}


char	*process_build_line(char *line, size_t offset, int last_chunk)
{
	if (last_chunk == -1 && offset == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*build_line(t_buf_mngr **rd_chrs, size_t total_len, int last_chunk)
{
	t_buf_mngr	*temp;
	char		*line;
	size_t		offset;
	if (!init_build_line(rd_chrs, &line, total_len))
		return (NULL);
	temp = *rd_chrs;
	offset = 0;
	while (temp && temp->content)
	{
		offset += copy_content(line, offset, temp);
		process_temp_node(rd_chrs, temp);
		temp = *rd_chrs;
	}
	line[offset] = '\0';
	return (process_build_line(line, offset, last_chunk));
}
