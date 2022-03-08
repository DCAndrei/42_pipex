/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 13:18:56 by acretu            #+#    #+#             */
/*   Updated: 2022/01/15 19:54:28 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_any_child(char *cmd, char *envp[]);
void	ft_check_exec_c(char **command, int *fd, char *envp[], char *cmd);
void	ft_check_exec_p1(char **command, int *fd_out, char *envp[]);
void	ft_check_p2(int argc, char *argv[], char *envp[], int *fd_out);

int	main(int argc, char *argv[], char *envp[])
{
	int		i;
	int		fd_in;
	int		fd_out;
	char	**command;

	if (argc > 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
			i = ft_set_fd_gnl(argv, &fd_out, argc);
		else
			i = ft_set_fd(argv, &fd_in, &fd_out, argc);
		while (i++ < argc - 2)
			ft_any_child(argv[i - 1], envp);
		command = ft_check_cmd(argv[argc - 2]);
		if (command != NULL)
			ft_check_exec_p1(command, &fd_out, envp);
		else
		{
			ft_check_p2(argc, argv, envp, &fd_out);
			ft_free (command);
			ft_execute(argv[argc - 2], envp);
		}
	}
	else
		ft_print_error(2);
}

void	ft_any_child(char *cmd, char *envp[])
{
	int		fd[2];
	int		pid;
	char	**command;

	if (pipe(fd) == -1)
		ft_error();
	pid = fork();
	if (pid == -1)
		ft_error();
	if (pid == 0)
	{
		close(fd[0]);
		command = ft_check_cmd(cmd);
		ft_check_exec_c(command, fd, envp, cmd);
	}
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			ft_error();
		close(fd[0]);
		waitpid(-1, NULL, WNOHANG);
	}
}

void	ft_check_exec_c(char **command, int *fd, char *envp[], char *cmd)
{
	if (command != NULL)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			ft_error();
		close (fd[1]);
		if (execve(command[0], command, envp) == -1)
		{
			ft_free(command);
			ft_error();
		}
	}
	else
	{
		if (ft_check_path(cmd, envp) == 1)
			ft_cmd_error(cmd);
		free(command);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			ft_error();
		close (fd[1]);
		ft_execute(cmd, envp);
	}
}

void	ft_check_exec_p1(char **command, int *fd_out, char *envp[])
{
	if (dup2(*fd_out, STDOUT_FILENO) == -1)
		ft_error();
	close (*fd_out);
	if (execve(command[0], command, envp) == -1)
	{
		ft_free(command);
		ft_error();
	}
}

void	ft_check_p2(int argc, char *argv[], char *envp[], int *fd_out)
{
	if (ft_check_path(argv[argc -2], envp) == 1)
		ft_cmd_error(argv[argc - 2]);
	if (dup2(*fd_out, STDOUT_FILENO) == -1)
		ft_error();
	close (*fd_out);
}
