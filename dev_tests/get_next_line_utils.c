/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:36:35 by luiza             #+#    #+#             */
/*   Updated: 2025/03/03 23:29:45 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*gnl_strchr(const char *s, int c)
{
	unsigned char	uc;

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

void	*gnl_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if (!dest || !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (dest != src)
	{
		while (n--)
			*d++ = *s++;
	}
	return (dest);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*new_str;

	if (!s2)
		return (NULL);
	len1 = gnl_strlen(s1);
	len2 = gnl_strlen(s2);
	new_str = malloc(len1 + len2 + 1);
	if (!new_str)
		return (NULL);
	if (s1)
	{
		gnl_memcpy(new_str, s1, len1);
		free(s1);
	}
	gnl_memcpy(new_str + len1, s2, len2);
	new_str[len1 + len2] = '\0';
	return (new_str);
}

char	*gnl_strdup(const char *s)
{
	char	*dup;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	len = 0;
	while (s[len])
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

char	*gnl_substr(char *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	slen;
	size_t	i;

	if (!s)
		return (NULL);
	slen = gnl_strlen(s);
	if (start >= slen)
		return (gnl_strdup(""));
	if (len > slen - start)
		len = slen - start;
	res = (char *)malloc(len + 1);
	i = 0;
	if (!res)
		return (NULL);
	while (i < len)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

t_buf_mngr	*find_or_create_node(t_buf_mngr **list, int fd)
{
	t_buf_mngr	*node;

	node =  *list;
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

static int	handle_read_error(char *buffer)
{
	free(buffer);
	return (-1);
}

static int	process_buffer(int fd, char *buffer, char **content)
{
	int		bytes;
	char	*temp;

	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes < 0)
		return (-1);
	buffer[bytes] = '\0';
	temp = gnl_strjoin(*content, buffer);
	if (!temp)
		return (-1);
	*content = temp;
	return (bytes);
}

int	read_to_buffer(int fd, char **content)
{
	char	*buffer;
	int		bytes;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (-1);
	bytes = 1;
	while (!gnl_strchr(*content, '\n') && bytes > 0)
	{
		bytes = process_buffer(fd, buffer, content);
		if (bytes < 0)
			return (handle_read_error(buffer));
	}
	free(buffer);
	return (bytes);
}

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
