/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:59:06 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/07/06 19:15:59 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	remove_heredoc(t_multi *pipex, char **env)
{
	char	*cmd[3];
	char	*cmd_file;

	cmd[0] = "rm";
	cmd[1] = ".here_doc";
	cmd[2] = NULL;
	if (pipex->here_doc == 0)
		return ;
	if (access(".here_doc", F_OK) == 0)
	{
		cmd_file = find_cmd_file(cmd, env);
		if (cmd_file == NULL)
		{
			free_array(cmd);
			exit(EXIT_FAILURE);
		}
		execve(cmd_file, cmd, env);
		free_array(cmd);
		error_return("execve");
	}
}

int	is_heredoc(char **argv, t_multi *pipex)
{
	if (argv[1] == NULL)
		return (0);
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		pipex->here_doc = 1;
		return (1);
	}
	pipex->here_doc = 0;
	return (0);
}

void	wait_loop(t_multi *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_qty)
	{
		wait(NULL);
		i++;
	}
}

char	*ft_trim(char *line, char c)
{
	char	*trim;
	int		i;

	i = 0;
	while (line[i] && line[i] != c)
		i++;
	trim = malloc((i + 1) * sizeof(char));
	if (!trim)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != c)
	{
		trim[i] = line[i];
		i++;
	}
	trim[i] = '\0';
	return (trim);
}
