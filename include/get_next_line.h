/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:03:49 by lukorman          #+#    #+#             */
/*   Updated: 2025/02/28 18:32:19 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_buf_mngr
{
	char				*content;
	struct s_buf_mngr	*next;
}	t_buf_mngr;

typedef struct s_read_file
{
	int			fd;
	char		*buf;
	ssize_t		i;
	ssize_t		rd;
}	t_read_file;

char		*get_next_line(int fd);
char		*read_line_from_file(t_read_file *file);
t_buf_mngr	*add_node(t_buf_mngr **head, const char *str);
void		*free_list(t_buf_mngr **head);
void		free_static_buffer(t_read_file *file);
void		process_temp_node(t_buf_mngr **rd_chrs, t_buf_mngr *temp);
char		*gnl_strchr(const char *s, int c);
char		*gnl_strdup(const char *s);
void		*gnl_memcpy(void *dest, const void *src, size_t n);
char		*build_line(t_buf_mngr **rd_chrs, size_t total_len,
				int last_chunk);
char		*process_build_line(char *line, size_t offset, int last_chunk);
ssize_t		read_next_chunk(t_read_file *file, char *chunk);
char		*process_read_line(t_buf_mngr *rd_chrs, size_t total_len,
				int last_chunk);

#endif
