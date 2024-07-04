/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:59:06 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/07/04 15:59:18 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	wait_loop(t_multi *pipex)
{
	int 	i;

	i = 0;
	while (i < pipex->cmd_qty)
	{
		wait(NULL);
		i++;
	}
}

void	close_all_pipes(t_multi *pipex)
{
	close(pipex->pipe_fd[0][0]);
	close(pipex->pipe_fd[0][1]);
	close(pipex->pipe_fd[1][0]);
	close(pipex->pipe_fd[1][1]);
}

void	create_pipes(t_multi *pipex)
{
	if (pipe(pipex->pipe_fd[0]) == -1)
		error_exit("pipe 0");
	if (pipe(pipex->pipe_fd[1]) == -1)
		error_exit("pipe 1");
}
