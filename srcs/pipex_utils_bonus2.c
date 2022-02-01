/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 13:05:05 by acretu            #+#    #+#             */
/*   Updated: 2022/01/15 17:51:05 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_set_fd(char *argv[], int *fd_in, int *fd_out, int argc)
{
	*fd_in = open(argv[1], O_RDONLY, 0777);
	if (*fd_in < 0)
		ft_file_error(argv[1]);
	*fd_out = open(argv[argc - 1], O_WRONLY | O_TRUNC, 07777);
	if (*fd_out < 0)
		ft_file_error(argv[argc - 1]);
	if (dup2(*fd_in, STDIN_FILENO) == -1)
		ft_error();
	close (*fd_in);
	return (2);
}

int	ft_set_fd_gnl(char *argv[], int *fd_out, int argc)
{
	*fd_out = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (*fd_out < 0)
		ft_file_error(argv[argc - 1]);
	ft_get_lines(argv[2], argc);
	return (3);
}

void	ft_get_lines(char *limiter, int argc)
{
	int		fd[2];
	int		pid;

	if (argc >= 6)
	{
		if (pipe(fd) == -1)
			ft_error();
		pid = fork();
		if (pid == 0)
			ft_iteration_lines(limiter, fd);
		else
		{
			close (fd[1]);
			if (dup2(fd[0], STDIN_FILENO) == -1)
				ft_error();
			close (fd[0]);
			wait(NULL);
		}
	}
	else
		ft_print_error(1);
}

void	ft_print_error(int nb)
{
	if (nb == 1)
	{
		ft_putendl("Error: Bad arguments");
		ft_putendl("Expected: ./pipex here_doc LIMITER cmd cmd1 ... cmdn file");
		exit(EXIT_FAILURE);
	}
	else if (nb == 2)
	{
		ft_putendl("Error: Bad arguments");
		ft_putstr("Expected: ./pipex file1 cmd1 cmd2 ... cmdn file2 OR");
		ft_putendl(" ./pipex here_doc LIMITER cmd cmd1 ... cmdn file");
		exit(EXIT_FAILURE);
	}
}

void	ft_iteration_lines(char *limiter, int *fd)
{
	char	*line;

	close (fd[0]);
	ft_putstr("pipe heredoc> ");
	line = get_next_line(STDIN_FILENO);
	while (line != NULL)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
		ft_putstr("pipe heredoc> ");
		line = get_next_line(STDIN_FILENO);
	}
}
