/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:03:58 by lukorman          #+#    #+#             */
/*   Updated: 2025/02/02 13:01:47 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_buf_mngr	*add_node(t_buf_mngr **head, const char *str)
{
	t_buf_mngr *new_node;
    t_buf_mngr *current;

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
	{
        *head = new_node;
		return (new_node);
	}
	current = *head;
    while (current->next != NULL)
	{
        current = current->next;
	}
	current->next = new_node;
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

int	read_next_chunk(t_read_file *file, char *chunk)
{
	size_t	chunk_len;

	if (!file || !chunk || file->buf == NULL)
		return (0);
	chunk_len = 0;
	if (file->i >= file->rd)
	{
        file->rd = read(file->fd, file->buf, BUFFER_SIZE);
        if (file->rd <= 0)
            return (0);
        file->i = 0;
    }
	while (file->i < file->rd && chunk_len < BUFFER_SIZE)
	{
		chunk[chunk_len++] = file->buf[file->i++];
		if(chunk[chunk_len -1] == '\n')
			break ;
	}
	chunk[chunk_len] = '\0';
	return ((int)chunk_len);
}

char *gnl_strdup(const char *s)
{
    char *dup;
    size_t len;
    size_t i;

	if (!s)
		return (NULL);
	len = 0;
    while (s[len] != '\0')
		len++;
    dup = (char *)malloc(len + 1);
    if (!dup)
        return (NULL);
    i = 0;
    while (i < len)
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char uc;
	if (!s)
		return (NULL);
	uc = (unsigned char)c;
	while (*s)
	{
		if (*(unsigned char *)s == uc)
            return ((char *)s);
        s++;
	}
	if (uc == '\0')
        return ((char *)s);
	return (NULL);
}
