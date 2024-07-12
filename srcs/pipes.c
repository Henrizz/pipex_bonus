/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:38:41 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/07/10 16:57:24 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	create_pipes(t_multi *pipex)
{
	int	i;

	i = 0;
	pipex->cmd_i = 0;
	pipex->inf_fd = -1;
	pipex->outf_fd = -1;
	pipex->curr = 0;
	pipex->prev = 0;
	pipex->denied_acc = 0;
	pipex->pipe_fd = malloc((pipex->cmd_qty - 1) * sizeof(int *));
	if (pipex->pipe_fd == NULL)
		error_exit("malloc");
	while (i < pipex->cmd_qty - 1)
	{
		pipex->pipe_fd[i] = malloc(2 * sizeof(int));
		if (pipex->pipe_fd[i] == NULL)
			error_exit("malloc");
		if (pipe(pipex->pipe_fd[i]) == -1)
			error_exit("pipe");
		i++;
	}
}

void	replace_pipes(t_multi *pipex)
{
	if (pipex->cmd_i == 0)
	{
		if (dup2(pipex->inf_fd, 0) == -1)
			error_return("dup2 infile");
		if (dup2(pipex->pipe_fd[pipex->cmd_i][1], 1) == -1)
			error_return("dup2 pipe[current][1]");
	}
	else if (pipex->cmd_i == pipex->cmd_qty - 1)
	{
		if (dup2(pipex->pipe_fd[pipex->cmd_i - 1][0], 0) == -1)
			error_return("dup2 pipe[previous][0]");
		if (dup2(pipex->outf_fd, 1) == -1)
			error_return("dup2 outfile");
	}
	else
	{
		if (dup2(pipex->pipe_fd[pipex->cmd_i - 1][0], 0) == -1)
			error_return("dup2 pipe[previous][0]");
		close(pipex->pipe_fd[pipex->cmd_i - 1][0]);
		if (dup2(pipex->pipe_fd[pipex->cmd_i][1], 1) == -1)
			error_return("dup2 pipe[current][1]");
		close(pipex->pipe_fd[pipex->cmd_i][1]);
	}
}

void	close_all_pipes(t_multi *pipex)
{
	int	i;

	i = 0;
	if (pipex->inf_fd != -1)
		close(pipex->inf_fd);
	if (pipex->outf_fd != -1)
		close(pipex->outf_fd);
	while (i < pipex->cmd_qty - 1)
	{
		if (pipex->pipe_fd[i][0] != -1)
			close(pipex->pipe_fd[i][0]);
		if (pipex->pipe_fd[i][1] != -1)
			close(pipex->pipe_fd[i][1]);
		free(pipex->pipe_fd[i]);
		i++;
	}
	free(pipex->pipe_fd);
}
