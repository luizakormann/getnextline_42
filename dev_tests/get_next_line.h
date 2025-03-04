/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:03:49 by lukorman          #+#    #+#             */
/*   Updated: 2025/03/03 23:19:48 by luiza            ###   ########.fr       */
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
	int					fd;
	char				*content;
	struct s_buf_mngr	*next;
}	t_buf_mngr;

char		*get_next_line(int fd);
t_buf_mngr	*find_or_create_node(t_buf_mngr **list, int fd);
int			read_to_buffer(int fd, char **content);
char		*extract_line(char **content);
void		free_node(t_buf_mngr **list, int fd);
char		*gnl_substr(char *s, unsigned int start, size_t len);
size_t		gnl_strlen(const char *s);
char		*gnl_strchr(const char *s, int c);
char		*gnl_strjoin(char *s1, char *s2);
char		*gnl_strdup(const char *s);
void		*gnl_memcpy(void *dest, const void *src, size_t n);
#endif
