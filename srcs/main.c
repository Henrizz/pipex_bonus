/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:02:29 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/07/04 16:34:06 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **env)
{
	int	pid;
	t_multi	pipex;

	if (argc < 5)
		return (print_exit("Error: not enough arguments\n"));
	create_pipes(&pipex);
	permissions_and_open(argc, argv, &pipex);
	//permissions_and_open(argv[1], argv[2], argv[argc - 1], &pipex);
	pipex.cmd_qty = argc - 3 - 1;
	pipex.cmd_i = 0;
	while (pipex.cmd_i < pipex.cmd_qty) //fork all child processes
	{
		pipex.curr = pipex.cmd_i % 2;
		pipex.prev = (pipex.cmd_i + 1) % 2;
		pid = fork();
		if (pid == -1)
			return (error_return("fork"));
		if (pid == 0)
			child_process_bonus(argv, env, &pipex);
		pipex.cmd_i++;
	}
	close(pipex.inf_fd);
	close(pipex.outf_fd);
	close_all_pipes(&pipex);
	wait_loop(&pipex);
	return (0);
}


int	child_process_bonus(char **argv, char **env, t_multi *pipex)
{
	char	*cmd_file;
	char	**cmd;

	// close all relevant ends per condition of first last or middle command
	close_selected_pipes(pipex);
	replace_pipes(pipex);
	//close_all_pipes(pipex);
	if (argv[pipex->cmd_i + 2][0] == '\0')
		exit(EXIT_FAILURE);
	cmd = ft_split(argv[pipex->cmd_i + 2], ' ');
	cmd_file = find_cmd_file(cmd, env);
	if (cmd_file == NULL)
	{
		free(cmd_file);
		free_array(cmd);
		exit(EXIT_FAILURE);
	}
	execve(cmd_file, cmd, env);
	free_array(cmd);
	return (error_return("execve"));
}

void	replace_pipes(t_multi *pipex)
{
	if (pipex->cmd_i == 0) // first command
	{
		if (dup2(pipex->inf_fd, 0) == -1)
			error_return("dup2 infile");
		if (dup2(pipex->pipe_fd[pipex->curr][1], 1) == -1)
			error_return("dup2 pipe[current][1]");
	}
	else if (pipex->cmd_i == pipex->cmd_qty - 1) //last command
	{
		if (dup2(pipex->pipe_fd[pipex->prev][0], 0) == -1)
				error_return("dup2 pipe[previous][0]");
		if (dup2(pipex->outf_fd, 1) == -1)
				error_return("dup2 outfile");	
	}
	else
	{
		if (dup2(pipex->pipe_fd[pipex->prev][0], 0) == -1)
			error_return("dup2 pipe[previous][0]");
		if (dup2(pipex->pipe_fd[pipex->curr][1], 1) == -1)
			error_return("dup2 pipe[current][1]");
	}
}

void	close_selected_pipes(t_multi *pipex)
{
	if (pipex->cmd_i == 0) // first command
	{
		close(pipex->pipe_fd[pipex->curr][0]);
		close(pipex->pipe_fd[pipex->prev][0]);
		close(pipex->pipe_fd[pipex->prev][1]);
		
	}
	else if (pipex->cmd_i == pipex->cmd_qty - 1) //last command
	{
		if (dup2(pipex->pipe_fd[pipex->prev][0], 0) == -1)
				error_return("dup2 pipe[previous][0]");
		if (dup2(pipex->outf_fd, 1) == -1)
				error_return("dup2 outfile");	
		close(pipex->pipe_fd[pipex->curr][0]);
		close(pipex->pipe_fd[pipex->curr][1]);
		close(pipex->pipe_fd[pipex->prev][1]);
	}
	else
	{
		close(pipex->pipe_fd[pipex->curr][0]);
		close(pipex->pipe_fd[pipex->prev][1]);
	}
}

