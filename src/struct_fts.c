/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_fts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:52:24 by luiza             #+#    #+#             */
/*   Updated: 2025/02/28 13:01:37 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

t_buf_mngr	*add_node(t_buf_mngr **head, const char *str)
{
	t_buf_mngr	*new_node;
	t_buf_mngr	*current;

	if (!str)
		return (NULL);
	new_node = malloc(sizeof(t_buf_mngr));
	if (!new_node)
		return (NULL);
	new_node->content = gnl_strdup(str);
	if (!new_node->content)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
	return (new_node);
}

void	*free_list(t_buf_mngr **head)
{
	t_buf_mngr	*current;
	t_buf_mngr	*next;

	if (!head || !*head)
		return (NULL);
	current = *head;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*head = NULL;
	return (NULL);
}

void	process_temp_node(t_buf_mngr **rd_chrs, t_buf_mngr *temp)
{
	*rd_chrs = temp->next;
	free(temp->content);
	free(temp);
}

void	free_static_buffer(t_read_file *file)
{
	if (file->buf)
	{
		free(file->buf);
		file->buf = NULL;
	}
}
