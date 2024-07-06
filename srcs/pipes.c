/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:38:41 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/07/06 17:39:53 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	create_pipes(t_multi *pipex)
{
	if (pipe(pipex->pipe_fd[0]) == -1)
		error_exit("pipe 0");
	if (pipe(pipex->pipe_fd[1]) == -1)
		error_exit("pipe 1");
}

void	replace_pipes(t_multi *pipex)
{
	if (pipex->cmd_i == 0)
	{
		if (dup2(pipex->inf_fd, 0) == -1)
			error_return("dup2 infile");
		if (dup2(pipex->pipe_fd[pipex->curr][1], 1) == -1)
			error_return("dup2 pipe[current][1]");
	}
	else if (pipex->cmd_i == pipex->cmd_qty - 1)
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
	if (pipex->cmd_i == 0)
	{
		close(pipex->pipe_fd[pipex->curr][0]);
		close(pipex->pipe_fd[pipex->prev][0]);
		close(pipex->pipe_fd[pipex->prev][1]);
	}
	else if (pipex->cmd_i == pipex->cmd_qty - 1)
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

void	close_all_pipes(t_multi *pipex)
{
	close(pipex->inf_fd);
	close(pipex->outf_fd);
	close(pipex->pipe_fd[0][0]);
	close(pipex->pipe_fd[0][1]);
	close(pipex->pipe_fd[1][0]);
	close(pipex->pipe_fd[1][1]);
}
