/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:36:35 by luiza             #+#    #+#             */
/*   Updated: 2025/03/02 00:11:49 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

static int	refill_buffer(t_read_file *file)
{
	ssize_t	check_read;

	check_read = read(file->fd, file->buf, BUFFER_SIZE);
	if (check_read < 0)
		return (-1);
	if (check_read == 0)
		return (0);
	file->rd = check_read;
	file->i = 0;
	return (1);
}

static char	*handle_chunk_processing(t_buf_mngr **rd_chrs, char *chunk,
			ssize_t chunk_len, size_t *total_len)
{
	if (chunk_len < 0)
	{
		free(chunk);
		free_list(rd_chrs);
		return (NULL);
	}
	if (chunk_len == 0)
	{
		free(chunk);
		if (!*rd_chrs)
		{
			free_list(rd_chrs);
			return (NULL);
		}
		return (build_line(rd_chrs, *total_len, 0));
	}
	if (!handle_chunk_read(rd_chrs, chunk, chunk_len, total_len))
	{
		free(chunk);
		return (NULL);
	}
	free(chunk);
	return ((char *)1);
}

ssize_t	read_next_chunk(t_read_file *file, char *chunk)
{
	size_t	chunk_len;
	int		read_result;

	if (!file || !chunk || !file->buf)
		return (-1);
	chunk_len = 0;
	while (chunk_len < BUFFER_SIZE)
	{
		if (file->i >= file->rd)
		{
			read_result = refill_buffer(file);
			if (read_result <= 0)
				return (read_result);
		}
		chunk[chunk_len++] = file->buf[file->i++];
		if (file->buf[file->i - 1] == '\n' || file->i >= file->rd)
			break ;
	}
	chunk[chunk_len] = '\0';
	return (chunk_len);
}

static int	init_reading(t_buf_mngr **rd_chrs, size_t *total_len,
			int *last_chunk)
{
	*rd_chrs = NULL;
	*total_len = 0;
	*last_chunk = 0;
	return (1);
}

static char	*cleanup_read_buffer(t_buf_mngr **rd_chrs, char **chunk)
{
	free(chunk);
	free_list(rd_chrs);
	chunk = NULL;
	return (NULL);
}

static char	*check_chunk(char *chunk)
{
	if (chunk == NULL)
		return (NULL);
	if (chunk != (char *)1)
		return (chunk);
	return ((char *)1);
}

char	*read_line_from_file(t_read_file *file)
{
	t_buf_mngr	*rd_chrs;
	char		*chunk;
	size_t		total_len;
	ssize_t		chunk_len;
	int			last_chunk;

	chunk = malloc(BUFFER_SIZE + 1);
	if (!chunk)
		return (NULL);
	ft_bzero(chunk, BUFFER_SIZE + 1);
	if (!init_reading(&rd_chrs, &total_len, &last_chunk))
		cleanup_read_buffer(&rd_chrs, &chunk);
	while (1)
	{
		chunk_len = read_next_chunk(file, chunk);
		if (gnl_strchr(chunk, '\n') != NULL || chunk == 0)
			last_chunk = 1;
		chunk = handle_chunk_processing(&rd_chrs, chunk, chunk_len, &total_len);
		check_chunk(chunk);
		if (last_chunk)
			break ;
	}
	return (process_read_line(rd_chrs, total_len, last_chunk));
}
