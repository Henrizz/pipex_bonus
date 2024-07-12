/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:02:22 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/07/10 16:57:03 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	find_command(char **argv, t_multi *pipex, char **cmd_file, char ***cmd)
{
	char	*temp;

	if (ft_strrchr(argv[pipex->cmd_i + 2], '/'))
	{
		*cmd_file = ft_trim(argv[pipex->cmd_i + 2], ' ');
		if (access(*cmd_file, X_OK) != 0)
		{
			ft_putstr_fd(*cmd_file, 2);
			ft_putstr_fd(": command not found\n", 2);
			return (-1);
		}
		temp = ft_strrchr(argv[pipex->cmd_i + 2], '/') + 1;
		*cmd = ft_split(temp, ' ');
		if (*cmd_file == NULL || *cmd[0] == NULL)
		{
			if (*cmd)
				free_array(*cmd);
			if (*cmd_file)
				free(*cmd_file);
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}

int	child_process_bonus(char **argv, char **env, t_multi *pipex)
{
	char	*cmd_file;
	char	**cmd;

	cmd_file = NULL;
	cmd = NULL;
	replace_pipes(pipex);
	close_all_pipes(pipex);
	if (argv[pipex->cmd_i + 2][0] == '\0')
		return (print_exit("Command '' not found\n"));
	if (ft_strrchr(argv[pipex->cmd_i + 2], '/'))
		find_command(argv, pipex, &cmd_file, &cmd);
	else
	{
		cmd = ft_split(argv[pipex->cmd_i + 2], ' ');
		cmd_file = find_cmd_file(cmd, env);
		if (cmd_file == NULL)
		{
			free_array(cmd);
			exit(EXIT_FAILURE);
		}
	}
	execve(cmd_file, cmd, env);
	free_array(cmd);
	return (error_exit("execve"));
}

char	*get_paths(char **env, char *name)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i] != NULL)
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strncmp(sub, name, 4) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*find_cmd_file(char **cmd, char **env)
{
	char	**paths;
	int		i;
	char	*cmd_file;
	char	*temp;

	i = 0;
	paths = ft_split(get_paths(env, "PATH"), ':');
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		cmd_file = ft_strjoin(temp, cmd[0]);
		free(temp);
		if (access(cmd_file, X_OK) == 0)
		{
			free_array(paths);
			return (cmd_file);
		}
		else
			free(cmd_file);
		i++;
	}
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_array(paths);
	return (NULL);
}
