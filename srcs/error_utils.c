/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:30:16 by acretu            #+#    #+#             */
/*   Updated: 2022/01/15 19:54:24 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_file_error(char *file)
{
	ft_putstr("Error: ");
	ft_putstr(strerror(errno));
	ft_putstr(": ");
	ft_putendl(file);
	exit (1);
}

void	ft_cmd_error(char *file)
{
	char	**cmmds;

	cmmds = ft_split(file, ' ');
	if (cmmds == NULL)
		ft_error();
	if (ft_strchr(cmmds[0], '/'))
	{
		ft_putstr("Error: no such file or directory: ");
		ft_putendl(cmmds[0]);
	}
	else
	{
		ft_putstr("Error: command not found: ");
		ft_putendl(cmmds[0]);
	}
	ft_free(cmmds);
	exit (127);
}

void	ft_error(void)
{
	perror("Error: ");
	exit(EXIT_FAILURE);
}

void	ft_change_fd_pt(int *fd_file, int *fd)
{
	close (fd[1]);
	if (dup2(fd[0], STDIN_FILENO) < 0)
		ft_error();
	close (fd[0]);
	if (dup2(*fd_file, STDOUT_FILENO) < 0)
		ft_error();
	close (*fd_file);
}

char	**ft_return_path(char *envp[])
{
	int		i;
	char	**path;

	i = 0;
	while (envp[i] != NULL && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	path = ft_split(envp[i] + 5, ':');
	if (path == NULL)
		return (NULL);
	return (path);
}
