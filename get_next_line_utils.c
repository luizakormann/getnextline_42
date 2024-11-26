/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:03:58 by lukorman          #+#    #+#             */
/*   Updated: 2024/11/26 20:21:50 by lukorman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_buf(t_buf_manager *buf)
{
	t_buf_manager	*temp_b;

	temp_b = buf; // inicialize temp.pointer to beggining of the list
	while (temp_b)
	{
		temp_b = temp_b->next; // advance to next node before clearing the node
		free(buf); // clear node
		buf = temp_b; // advance list to next node
	}
	return (NULL); // to-do study further the returning null
}
