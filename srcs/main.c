/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:02:29 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/07/06 19:14:59 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **env)
{
	int		pid;
	t_multi	pipex;

	if (argc < 5 + is_heredoc(argv, &pipex))
		return (print_exit("Error: not enough arguments\n"));
	create_pipes(&pipex);
	permissions_and_open(argc, argv, &pipex);
	pipex.cmd_qty = argc - 3 - pipex.here_doc;
	pipex.cmd_i = 0;
	while (pipex.cmd_i < pipex.cmd_qty)
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
	close_all_pipes(&pipex);
	wait_loop(&pipex);
	if (access (".here_doc", F_OK == 0))
		remove_heredoc(&pipex, env);
	return (0);
}
