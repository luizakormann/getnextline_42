/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:03:58 by lukorman          #+#    #+#             */
/*   Updated: 2024/11/27 22:39:50 by lukorman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_buf(t_buf_mngr *buf)
{
	t_buf_mngr	*temp_b;

	temp_b = buf;
	while (temp_b)
	{
		temp_b = temp_b->next;
		free(buf);
		buf = temp_b;
	}
	return (NULL);
}

t_buf_mngr	*node_manager(char c)
{
	t_buf_mngr	*new_char;

	new_char = malloc(sizeof(t_buf_mngr));
	if (!new_char)
		return (NULL);
	new_char->act_char = c;
	new_char->next = NULL;
	return (new_char);
}

void	add_node_manager(t_buf_mngr **read_chars, t_buf_mngr *new_char)
{
	t_buf_mngr	*temp;

	if (new_char)
	{
		if (!*read_chars)
			*read_chars = new_char;
		else
		{
			temp = *read_chars;
			while (temp->next)
				temp = temp->next;
			temp->next = new_char;
		}
	}
}

char	*read_buffer(t_read_file *file)
{
	file->len = 0;
	while (file->rd > 0)
	{
		add_node_manager(&file->read_chars, node_manager(file->buf[file->i]));
		if (file->buf[file->i] == '\n' || file->buf[file->i] == '\0')
			break ;
		file->i++;
		file->len++;
		if (file->i >= file->rd)
		{
			file->i = 0;
			file->rd = read(file->fd, file->buf, BUFFER_SIZE);
			if (file ->rd == ERROR)
				return (free_buf(file->read_chars));
		}
	}
	file->i++;
	file->len++;
	return (write_line(file));
}

char	*write_line(t_read_file *file)
{
	t_buf_mngr	*temp;
	char		*line;
	size_t		i;

	line = malloc((file->len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	temp = NULL;
	while (file->read_chars)
	{
		temp = file->read_chars->next;
		line[i++] = file->read_chars->act_char;
		free(file->read_chars);
		file->read_chars = temp;
	}
	line[i] = '\0';
	return (line);
}
