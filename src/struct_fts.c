/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_fts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:52:24 by luiza             #+#    #+#             */
/*   Updated: 2025/03/03 23:53:52 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

t_buf_mngr	*find_or_create_node(t_buf_mngr **list, int fd)
{
	t_buf_mngr	*node;

	node = *list;
	while (node)
	{
		if (node->fd == fd)
			return (node);
		node = node->next;
	}
	node = malloc(sizeof(t_buf_mngr));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->content = NULL;
	node->next = *list;
	*list = node;
	return (node);
}

void	free_node(t_buf_mngr **list, int fd)
{
	t_buf_mngr	*current;
	t_buf_mngr	*prev;

	current = *list;
	prev = NULL;
	while (current)
	{
		if (current->fd == fd)
		{
			if (prev)
				prev->next = current->next;
			else
				*list = current->next;
			free(current->content);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
