/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:03:55 by lukorman          #+#    #+#             */
/*   Updated: 2025/03/03 23:14:04 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_buf_mngr	*list;
	t_buf_mngr			*node;
	char				*line;
	int					bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = find_or_create_node(&list, fd);
	if (!node)
		return (NULL);
	bytes = read_to_buffer(fd, &node->content);
	if (bytes < 0)
	{
		free_node(&list, fd);
		return (NULL);
	}
	line = extract_line(&node->content);
	if (!line || !node->content)
		free_node(&list, fd);
	return (line);
}
