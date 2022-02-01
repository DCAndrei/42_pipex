/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:48:46 by acretu            #+#    #+#             */
/*   Updated: 2022/01/15 17:51:08 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_putstr(char *s)
{
	if (s == NULL)
		return ;
	while (*s != '\0')
	{
		write(1, s, sizeof(char));
		s++;
	}
}

void	ft_putendl(char *s)
{
	if (s == NULL)
		return ;
	while (*s != '\0')
	{
		write(1, s, sizeof(char));
		s++;
	}
	write(1, "\n", sizeof(char));
}

void	ft_execute(char *cmd, char *envp[])
{
	char	*path;
	char	**cmmds;

	cmmds = ft_split(cmd, ' ');
	if (cmmds == NULL)
		ft_error();
	path = ft_get_path(cmmds[0], envp);
	if (execve(path, cmmds, envp) == -1)
	{
		free(path);
		ft_free(cmmds);
		ft_error();
	}
}

char	*ft_get_path(char *cmd, char *envp[])
{
	char	*tmp;
	int		i;
	char	**path;
	char	*final_path;

	path = ft_return_path(envp);
	if (path == NULL)
		return (NULL);
	i = 0;
	while (path[i] != NULL)
	{
		tmp = ft_strjoin(path[i], "/");
		final_path = ft_strjoin(tmp, cmd);
		free (tmp);
		if (access(final_path, F_OK) == 0)
		{
			ft_free(path);
			return (final_path);
		}
		free(final_path);
		i++;
	}
	ft_free(path);
	return (NULL);
}

void	ft_change_fd_ch(int *fd_file, int *fd)
{
	if (dup2(*fd_file, STDIN_FILENO) < 0)
		ft_error();
	close (fd[0]);
	close (*fd_file);
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		ft_error();
	close (fd[1]);
}
