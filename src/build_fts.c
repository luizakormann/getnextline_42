/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_fts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:48:43 by luiza             #+#    #+#             */
/*   Updated: 2025/03/03 23:53:33 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

static void	free_and_set_null(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

static char	*get_line_content(char **content, int len)
{
	char	*line;

	if ((*content)[len] == '\n')
		line = gnl_substr(*content, 0, len + 1);
	else
		line = gnl_substr(*content, 0, len);
	return (line);
}

char	*extract_line(char **content)
{
	char	*line;
	char	*temp;
	int		len;

	if (!*content || **content == '\0')
	{
		free_and_set_null(content);
		return (NULL);
	}
	len = 0;
	while ((*content)[len] && (*content)[len] != '\n')
		len++;
	line = get_line_content(content, len);
	if (!line)
		return (NULL);
	if ((*content)[len] == '\0')
		temp = NULL;
	else
		temp = gnl_strdup(*content + len + 1);
	free(*content);
	*content = temp;
	return (line);
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
