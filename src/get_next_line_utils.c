/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:03:58 by lukorman          #+#    #+#             */
/*   Updated: 2025/02/14 21:38:37 by lukorman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

size_t	read_next_chunk(t_read_file *file, char *chunk)
{
	size_t	chunk_len;
	ssize_t	check_read;

	if (!file || !chunk || !file->buf)
		return (0);
	chunk_len = 0;
	if (file->i >= file->rd)
	{
		check_read = read(file->fd, file->buf, BUFFER_SIZE);
		if (check_read < 0)
		{
			free(file->buf);
			file->buf = NULL;
			file->rd = 0;
			file->i = 0;
			return (0);
		}
		file->rd = check_read;
		if (file->rd <= 0)
			return (0);
		file->i = 0;
	}
	while (file->i < file->rd && chunk_len < BUFFER_SIZE)
	{
		chunk[chunk_len++] = file->buf[file->i++];
		if (chunk[chunk_len -1] == '\n')
			break ;
	}
	chunk[chunk_len] = '\0';
	return (chunk_len);
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
