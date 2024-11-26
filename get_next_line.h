/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:03:49 by lukorman          #+#    #+#             */
/*   Updated: 2024/11/26 20:06:01 by lukorman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
# endif
# define FD_O_LIMIT 1024
# define NULL_TERM 1
# define ERROR -1

# include <fcntl.h>
# include <unistd.h>

typedef struct s_buf_manager
{
	char			act_char;
	t_buf_manager	*next;
}	t_buf_manager;

typedef struct s_read_file
{
	int				fd;
	ssize_t			i;
	ssize_t			len;
	ssize_t			rd;
	char			buf[BUFFER_SIZE];
	t_buf_manager	*read_chars;
}	t_read_file;

char	*get_next_line(int fd);
char	*free_buf(t_buf_manager *buf);

#endif
