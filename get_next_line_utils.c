/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:03:58 by lukorman          #+#    #+#             */
/*   Updated: 2024/12/05 18:08:20 by lukorman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char uc;
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

char	*ft_strdup(const char *s)
{
	size_t	slen;
	char	*d;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	d = (char *)malloc(slen + 1);
	if (!d)
		return (NULL);
	ft_memcpy(d, s, slen);
	d[slen] = '\0';
	return (d);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > slen - start)
		len = slen - start;
	if (len > SIZE_MAX - 1)
        return (NULL);
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	if (ft_memcpy(res, s + start, len) == NULL)
    {
        free(res);
        return (NULL);
    }

    res[len] = '\0';
    return (res);
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
