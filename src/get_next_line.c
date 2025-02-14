/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:03:55 by lukorman          #+#    #+#             */
/*   Updated: 2025/02/02 13:22:23 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*read_line_from_file(t_read_file *file);
char	*build_line(t_buf_mngr **rd_chrs, size_t total_len, int last_chunk);
void	*ft_memcpy(void *dest, const void *src, size_t n);


char	*get_next_line(int fd)
{
	static t_read_file	file[1024];
	char				*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (file[fd].buf == NULL|| file[fd].rd == 0)
	{
		file[fd].fd = fd;
		file[fd].buf = malloc(BUFFER_SIZE + 1);
		if (!file[fd].buf)
			return (NULL);
		file[fd].i = 0;
		file[fd].rd = 0;
	}
	line = read_line_from_file(&file[fd]);
	if (!line)
	{
		if (file[fd].buf)
		{
            free(file[fd].buf);
            file[fd].buf = NULL;
        }
		file[fd].buf = NULL;
		file[fd].i = 0;
		file[fd].rd = 0;
	}
	return (line);
}

char	*read_line_from_file(t_read_file *file)
{
	t_buf_mngr	*rd_chrs;
	char		chunk[BUFFER_SIZE + 1];
	size_t		total_len;
	size_t		chunk_len;
	int			last_chunk;

	rd_chrs = NULL;
	chunk[BUFFER_SIZE] = '\0';
	total_len = 0;
	last_chunk = 0;
	while (1)
	{
		chunk_len = read_next_chunk(file, chunk);
		if (chunk_len <= 0)
			break ;
		if (!add_node(&rd_chrs, chunk))
		{
			free_list(&rd_chrs);
			return (NULL);
		}
		total_len += chunk_len;
		if (ft_strchr(chunk, '\n'))
			break ;
	}
	if (!rd_chrs)
	{
		free_list(&rd_chrs);
		return (NULL);
	}
	if (chunk_len > 0)
		last_chunk = 1;
	else
		last_chunk = -1;
	return (build_line(&rd_chrs, total_len, last_chunk));
}

char	*build_line(t_buf_mngr **rd_chrs, size_t total_len, int last_chunk)
{
    t_buf_mngr *temp;
    size_t content_len;
    char *line;
	size_t offset;

	if (!rd_chrs || *rd_chrs == NULL || total_len == 0)
    	return (NULL);

	line = malloc(total_len + 1);
	printf("malloc OK");

    if (!line)
    {
		printf("malloc ERRADO");
        free_list(rd_chrs);
        return (NULL);
    }

	temp = *rd_chrs;
	offset = 0;

    while (temp)
    {
		printf("Copiando \"%s\" para a linha\n", temp->content);
        if (temp->content)
        {
			content_len = 0;
            while (temp->content[content_len])
                content_len++;
            if (offset + content_len <= total_len)
			{
                ft_memcpy(line + offset, temp->content, content_len);
                offset += content_len;
            }
        }
        *rd_chrs = temp->next;
        free(temp->content);
		free(temp);
		temp = *rd_chrs;
    }
    line[offset] = '\0';
    if (last_chunk == -1)
    {
        free(line);
        line = NULL;
    }
	printf("Linha final gerada: \"%s\"\n", line);
    return (line);
}
void	*ft_memcpy(void *dest, const void *src, size_t n)
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

