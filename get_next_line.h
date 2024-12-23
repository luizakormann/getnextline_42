/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:03:49 by lukorman          #+#    #+#             */
/*   Updated: 2024/12/05 17:31:49 by lukorman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

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
	char		*buf;
	ssize_t		i;
	ssize_t		rd;
};

char		*get_next_line(int fd);
int			read_next_char(t_read_file *file);
void		add_node(t_buf_mngr **head, char c);
char		*write_str(t_buf_mngr *head, size_t len);
void		*free_list(t_buf_mngr **head);
t_buf_mngr	*create_node(char c);

#endif