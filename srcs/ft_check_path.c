/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:53:32 by acretu            #+#    #+#             */
/*   Updated: 2022/01/15 19:27:22 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_check_path(char *cmd, char *envp[])
{
	char	*path;
	char	**cmmds;

	cmmds = ft_split(cmd, ' ');
	if (cmmds == NULL)
		ft_error();
	path = ft_get_path(cmmds[0], envp);
	ft_free (cmmds);
	if (path == NULL)
		return (1);
	free (path);
	return (0);
}

char	**ft_check_cmd(char *cmd)
{
	char	**cmmds;

	cmmds = ft_split(cmd, ' ');
	if (cmmds == NULL)
		ft_error();
	if (access(cmmds[0], F_OK) == 0)
	{
		return (cmmds);
	}
	ft_free(cmmds);
	return (NULL);
}
