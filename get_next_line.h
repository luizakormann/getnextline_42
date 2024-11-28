/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:03:49 by lukorman          #+#    #+#             */
/*   Updated: 2024/11/27 22:39:45 by lukorman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define FD_O_LIMIT 1024
# define ERROR -1

typedef struct s_buf_mngr	t_buf_mngr;
struct s_buf_mngr
{
	char		act_char;
	t_buf_mngr	*next;
};

typedef struct s_read_file	t_read_file;
struct s_read_file
{
	int			fd;
	ssize_t		i;
	ssize_t		len;
	ssize_t		rd;
	char		buf[BUFFER_SIZE];
	t_buf_mngr	*read_chars;
};

char		*get_next_line(int fd);
char		*free_buf(t_buf_mngr *buf);
t_buf_mngr	*node_manager(char c);
void		add_node_manager(t_buf_mngr **read_chars, t_buf_mngr *new_char);
char		*read_buffer(t_read_file *file);
char		*write_line(t_read_file *file);

#endif
