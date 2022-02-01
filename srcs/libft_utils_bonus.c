/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 13:24:15 by acretu            #+#    #+#             */
/*   Updated: 2022/01/15 17:50:48 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char const	*t1;
	unsigned char const	*t2;

	t1 = (unsigned char const *) s1;
	t2 = (unsigned char const *) s2;
	if (n == 0)
		return (0);
	while (*t1 != '\0' && *t1 == *t2 && n > 1)
	{
		t1++;
		t2++;
		n--;
	}
	if (n == 1 && *t1 == *t2)
		return (0);
	else
		return (*t1 - *t2);
}

char	*ft_strdup(char const *s)
{
	char		*str;
	size_t		len;
	size_t		i;

	str = NULL;
	len = 0;
	while (s[len] != '\0')
		len++;
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}

void	ft_free_gnl(char **val)
{
	char		*tmp;

	tmp = *val;
	free (tmp);
	*val = NULL;
}
