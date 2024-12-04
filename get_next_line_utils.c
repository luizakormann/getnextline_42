/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:03:58 by lukorman          #+#    #+#             */
/*   Updated: 2024/12/03 23:17:10 by lukorman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_buf_mngr	*create_node(char c)
{
	t_buf_mngr	*node;

	node = malloc(sizeof(t_buf_mngr));
	if (!node)
		return (NULL);
	node->act_char = c;
	node->next = NULL;
	return (node);
}

void	add_node(t_buf_mngr **head, char c)
{
	t_buf_mngr	*new_node;
	t_buf_mngr	*current;

	new_node = create_node(c);
	if (!new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	if (current != NULL)
	{
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}

void	free_list(t_buf_mngr **head)
{
	t_buf_mngr	*current;
	t_buf_mngr	*next;

	if (!head)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}

char	*write_str(t_buf_mngr *head, size_t len)
{
	char	*line;
	size_t	i;

	line = malloc(len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (head)
	{
		line[i++] = head->act_char;
		head = head->next;
	}
	line[i] = '\0';
	return (line);
}

int	read_next_char(t_read_file *file)
{
	if (file->i >= file->rd)
	{
		file->rd = read(file->fd, file->buf, BUFFER_SIZE);
		file->i = 0;
		if (file->rd < 0)
			return (-1);
		if (file->rd == 0)
			return (0);
	}
	return (file->buf[file->i++]);
}
