/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:02:22 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/07/04 16:02:36 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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
