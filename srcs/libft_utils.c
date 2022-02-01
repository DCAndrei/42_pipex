/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 19:15:06 by acretu            #+#    #+#             */
/*   Updated: 2022/01/15 17:50:53 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static size_t	ft_s_size(char const *s, char c);

char	**ft_split(char const *s, char c)
{
	char		**array;
	const char	*s_init;
	size_t		size;
	size_t		i;

	if (s == NULL)
		return (NULL);
	s_init = s;
	size = ft_s_size(s, c);
	array = (char **)malloc(sizeof(char *) * (size + 1));
	if (array == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		while (*s == c && *s != '\0')
			s++;
		s_init = ft_strchr(s, c);
		*(array + i) = ft_substr(s, 0, (s_init - s));
		s = s_init + 1;
		i++;
	}
	*(array + i) = NULL;
	return (array);
}

static size_t	ft_s_size(char const *s, char c)
{
	size_t		size;
	char const	*t;

	size = 0;
	if (*s == '\0')
		return (0);
	while (*s != '\0')
	{
		t = s;
		while (*t != '\0' && *t == c)
			t++;
		if (*t != '\0')
		{
			size++;
			t++;
		}
		while (*t != '\0' && *t != c)
			t++;
		s = t;
	}
	return (size);
}

char	*ft_strchr(char const *s, int c)
{
	while (*s != '\0' && *s != c)
		s++;
	if ((*s == '\0' && c == 0) || *s == c)
		return ((char *) s);
	else
		return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		len_s;
	size_t		len_ret;
	char		*ret;

	if (s == NULL)
		return (NULL);
	len_s = 0;
	while (s[len_s] != '\0')
		len_s++;
	if (start > len_s)
	{
		ret = (char *)malloc(sizeof(char));
		if (ret == NULL)
			return (NULL);
		*ret = '\0';
		return (ret);
	}
	len_ret = len_s - start;
	if (len < len_ret)
		len_ret = len;
	ret = (char *)malloc(len_ret + 1);
	if (ret == NULL)
		return (NULL);
	ft_strlcpy(ret, (s + start), len_ret + 1);
	return (ret);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		len;

	len = 0;
	while (src[len] != '\0')
		len++;
	if (dstsize == 0)
		return (len);
	while (*src != '\0' && dstsize > 1)
	{
		*dst = *src;
		dst++;
		src++;
		dstsize--;
	}
	*dst = '\0';
	return (len);
}
