/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 19:29:32 by acretu            #+#    #+#             */
/*   Updated: 2022/01/15 17:50:59 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static	int	ft_find(const char *big, const char *little, size_t len);

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		len_little;

	if (*little == '\0')
		return ((char *)big);
	len_little = 0;
	while (little[len_little] != '\0')
		len_little++;
	while (*big != '\0' && len > 0)
	{
		if (len < len_little)
			return (NULL);
		if (*big == *little)
			if (ft_find(big, little, len))
				return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}

static	int	ft_find(const char *big, const char *little, size_t len)
{
	while (*little != '\0' && *little == *big && len)
	{
		little++;
		big++;
		len--;
	}
	if (*little == '\0')
		return (1);
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*ret;
	size_t		s1_len;
	size_t		s2_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ret = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (ret == NULL)
		return (NULL);
	ft_strlcpy(ret, s1, s1_len + 1);
	ft_strlcpy(ret + s1_len, s2, s2_len + 1);
	return (ret);
}

size_t	ft_strlen(char const *str)
{
	size_t		len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

void	ft_free(char **str)
{
	int		i;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i] != NULL)
		i++;
	while (i >= 0)
	{
		free (str[i]);
		i--;
	}
	free (str);
}
