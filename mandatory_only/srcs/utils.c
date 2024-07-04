/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 19:32:02 by Henriette         #+#    #+#             */
/*   Updated: 2024/06/20 16:15:31 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	error_return(char *message)
{
	perror(message);
	return (0);
}

void	free_array(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	check_permissions(char *infile, char *outfile)
{
	int	fd;

	if (access(infile, R_OK) == -1)
		return (error_return(infile));
	if (access(outfile, W_OK) == -1)
	{
		if (access(outfile, F_OK) == -1)
		{
			fd = open(outfile, O_WRONLY | O_CREAT, 0644);
			if (fd == -1)
				return (error_return(outfile));
			else
			{
				close(fd);
				return (1);
			}
		}
		return (error_return(outfile));
	}
	return (1);
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
