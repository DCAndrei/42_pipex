/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:45:25 by acretu            #+#    #+#             */
/*   Updated: 2022/01/15 14:46:07 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>

# define BUFFER_SIZE 1000
# define MAX_FD 10240

void	ft_putstr(char *s);
void	ft_putendl(char *s);
void	ft_execute(char *cmd, char *envp[]);
char	*ft_get_path(char *cmd, char *envp[]);
void	ft_change_fd_ch(int *fd_file, int *fd);

int		ft_check_path(char *cmd, char *envp[]);
char	**ft_check_cmd(char *cmd);

void	ft_error(void);
void	ft_free(char **str);
void	ft_file_error(char *file);
void	ft_cmd_error(char *file);
void	ft_change_fd_pt(int *fd_file, int *fd);
char	**ft_return_path(char *envp[]);

char	*ft_strchr(char const *s, int c);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(char const *str);

/*
BONUS FUNCTIONS
*/

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*get_next_line(int fd);
char	*ft_strdup(const char *s);
void	ft_free_gnl(char **val);

int		ft_set_fd(char *argv[], int *fd_in, int *fd_out, int argc);
int		ft_set_fd_gnl(char *argv[], int *fd_out, int argc);
void	ft_get_lines(char *limiter, int argc);
void	ft_print_error(int nb);
void	ft_iteration_lines(char *limiter, int *fd);

#endif