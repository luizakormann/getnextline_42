/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:36:35 by luiza             #+#    #+#             */
/*   Updated: 2025/02/28 18:31:02 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

static int	process_chunk(t_buf_mngr **rd_chrs, char *chunk,
			size_t chunk_len, size_t *total_len)
{
	if (!add_node(rd_chrs, chunk))
		return (0);
	*total_len += chunk_len;
	return (1);
}

static int	handle_chunk_read(t_buf_mngr **rd_chrs, char *chunk,
			size_t chunk_len, size_t *total_len)
{
	if (!process_chunk(rd_chrs, chunk, chunk_len, total_len))
	{
		free_list(rd_chrs);
		return (0);
	}
	return (1);
}

ssize_t	read_next_chunk(t_read_file *file, char *chunk)
{
	size_t	chunk_len;
	ssize_t	check_read;

	if (!file || !chunk || !file->buf)
		return (-1);
	chunk_len = 0;
	while (chunk_len < BUFFER_SIZE)
	{
		if (file->i >= file->rd)
		{
			check_read = read(file->fd, file->buf, BUFFER_SIZE);
			if (check_read < 0)
			{
				free(file->buf);
				file->buf = NULL;
				return (-1);
			}
			if (check_read == 0)
				return (0);
			file->rd = check_read;
			file->i = 0;
		}
		chunk[chunk_len++] = file->buf[file->i++];
		if (file->buf[file->i - 1] == '\n' || file->i >= file->rd)
			break ;
	}
	chunk[chunk_len] = '\0';
	return (chunk_len);
}

char	*read_line_from_file(t_read_file *file)
{
	t_buf_mngr	*rd_chrs;
	char		*chunk;
	size_t		total_len;
	ssize_t		chunk_len;
	int			last_chunk;

	rd_chrs = NULL;
	chunk = malloc(BUFFER_SIZE + 1);
	if (!chunk)
		return (NULL);
	total_len = 0;
	last_chunk = 0;
	while (1)
	{
		chunk_len = read_next_chunk(file, chunk);
		if (chunk_len < 0)
		{
			free(chunk);
			free_list(&rd_chrs);
			return (NULL);
		}
		if (chunk_len == 0)
		{
			free(chunk);
			if (!rd_chrs)
				return (NULL);
			return (build_line(&rd_chrs, total_len, 0));
		}
		if (!handle_chunk_read(&rd_chrs, chunk, chunk_len, &total_len))
		{
			free(chunk);
			return (NULL);
		}
		if (gnl_strchr(chunk, '\n'))
		{
			last_chunk = 1;
			break ;
		}
	}
	free(chunk);
	return (process_read_line(rd_chrs, total_len, last_chunk));
}
