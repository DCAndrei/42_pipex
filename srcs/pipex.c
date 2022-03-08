/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:45:56 by acretu            #+#    #+#             */
/*   Updated: 2022/01/15 19:32:38 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_error(void);
void	ft_child(char *argv[], char *envp[], int *fd);
void	ft_parent(char *argv[], char *envp[], int *fd);

int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	int		pid;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			ft_error();
		pid = fork();
		if (pid == -1)
			ft_error();
		if (pid == 0)
			ft_child(argv, envp, fd);
		waitpid(-1, NULL, WNOHANG);
		ft_parent(argv, envp, fd);
	}
	else
	{
		ft_putendl("Error: Bad arguments");
		ft_putendl("Expected: ./pipex file1 cmd1 cmd2 file2");
		exit(EXIT_FAILURE);
	}
	return (0);
}

void	ft_child(char *argv[], char *envp[], int *fd)
{
	int		fd_file;
	char	**command;

	fd_file = open(argv[1], O_RDONLY, 0777);
	if (fd_file < 0)
		ft_file_error(argv[1]);
	command = ft_check_cmd(argv[2]);
	if (command != NULL)
	{
		ft_change_fd_ch(&fd_file, fd);
		if (execve(command[0], command, envp) == -1)
		{
			ft_free(command);
			ft_error();
		}
	}
	else
	{
		if (ft_check_path(argv[2], envp) == 1)
			ft_cmd_error(argv[2]);
		free (command);
		ft_change_fd_ch(&fd_file, fd);
		ft_execute(argv[2], envp);
	}
}

void	ft_parent(char *argv[], char *envp[], int *fd)
{
	int		fd_file;
	char	**command;

	fd_file = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd_file < 0)
		ft_file_error(argv[4]);
	command = ft_check_cmd(argv[3]);
	if (command != NULL)
	{
		ft_change_fd_pt(&fd_file, fd);
		if (execve(command[0], command, envp) == -1)
		{
			ft_free(command);
			ft_error();
		}
	}
	else
	{
		if (ft_check_path(argv[3], envp) == 1)
			ft_cmd_error(argv[3]);
		ft_change_fd_pt(&fd_file, fd);
		free (command);
		ft_execute(argv[3], envp);
	}
}
