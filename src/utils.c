/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:03:58 by lukorman          #+#    #+#             */
/*   Updated: 2025/02/17 12:18:20 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

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

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	gnl_strncat(char *dst, const char *src, size_t size)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;

	dlen = gnl_strlen(dst);
	slen = gnl_strlen(src);
	i = 0;
	if (size <= dlen)
		return (size + slen);
	while (src[i] && dlen + i + 1 < size)
	{
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + i] = '\0';
	return (dlen + slen);
}
