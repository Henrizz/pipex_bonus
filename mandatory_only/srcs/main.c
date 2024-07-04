/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:02:29 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/06/20 14:41:55 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **env)
{
	int	i;
	int	pid;
	int	pipe_fd[2];

	i = 0;
	if (argc != 5)
		return (0);
	check_permissions(argv[1], argv[4]);
	if (pipe(pipe_fd) == -1)
		return (error_return("pipe"));
	pid = fork();
	if (pid == -1)
		return (error_return("fork"));
	if (pid == 0)
		child_process(argv, env, pipe_fd);
	else 
		parent_process(argv, env, pipe_fd, pid);
	return (0);
}

int	parent_process(char **argv, char **env, int *pipe_fd, int pid)
{
	int		fd;
	char	*cmd_file;
	char	**cmd;

	close(pipe_fd[1]);
	fd = open(argv[4], O_WRONLY);
	if (fd == -1)
		return (0);
	dup2(fd, 1);
	dup2(pipe_fd[0], 0);
	if (argv[3][0] == '\0')
		exit(EXIT_FAILURE);
	cmd = ft_split(argv[3], ' ');
	cmd_file = find_cmd_file(cmd, env);
	if (cmd_file == NULL)
	{
		free(cmd_file);
		free_array(cmd);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
	execve(cmd_file, cmd, env);
	free(cmd);
	return (0);
}

int	child_process(char **argv, char **env, int *pipe_fd)
{
	char	*cmd_file;
	char	**cmd;
	int		fd;

	close(pipe_fd[0]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (0);
	dup2(fd, 0);
	dup2(pipe_fd[1], 1);
	if (argv[2][0] == '\0')
		exit(EXIT_FAILURE);
	cmd = ft_split(argv[2], ' ');
	cmd_file = find_cmd_file(cmd, env);
	if (cmd_file == NULL)
	{
		free(cmd_file);
		free_array(cmd);
		exit(EXIT_FAILURE);
	}
	execve(cmd_file, cmd, env);
	free_array(cmd);
	return (0);
}
