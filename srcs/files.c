/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:01:00 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/07/06 16:21:51 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	permissions_and_open(int argc, char **argv, t_multi *pipex)
{
	int	fd;
	char *infile;
	char *outfile;

	infile = argv[1];
	outfile = argv[argc - 1];
	if (!ft_strncmp(infile, "here_doc", 8))
	{
		fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (error_exit("here_doc"));
		get_input_append(fd, argv, outfile, pipex);
		//get_input_append(fd, delim, outfile, pipex);
	}
	else
	{
		if (access(infile, R_OK) == -1)
			return (error_exit(infile));
		if (access(outfile, W_OK) == -1 && access(outfile, F_OK) == 0)
			return (error_exit(outfile));
		open_files(infile, outfile, pipex);
	}
	return (1);
}

void	get_input_append(int fd, char **argv, char *outfile, t_multi *pipex)
{
	char	*line;
	//check for errors in Delimiter name
	while (1)
	{
		line = get_next_line_new(0);
		if (line == NULL)
		{
			ft_putstr_fd("test1\n", 2);
			return;
		}	
		if (!ft_strncmp(line, argv[2], ft_strlen(argv[2])))
		{
			ft_putstr_fd("test2\n", 2);
			//ft_printf("endoffile\n");
			free(line);
			break;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
	if (access(outfile, W_OK) == -1 && access(outfile, F_OK) == 0)
			error_exit(outfile);
	pipex->inf_fd = open("here_doc", O_RDONLY);
	pipex->outf_fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (pipex->inf_fd == -1 || pipex->outf_fd == -1)
		error_exit("open");
	int i = 0;
	while (argv[3 + i])
	{
		//ft_printf("%s\n", argv[2 + i]);
		argv[2 + i] = argv[3 + i];
		i++;
	}
	argv[2 + i] = NULL;
}


/*int	permissions_and_open(char *infile, char *delim, char *outfile, t_multi *pipex)
{
	int	fd;
	
	if (!ft_strncmp(infile, "here_doc", 8))
	{
		fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (error_exit("here_doc"));
		get_input_append(fd, delim, outfile, pipex);
	}
	else
	{
		if (access(infile, R_OK) == -1)
			return (error_exit(infile));
		if (access(outfile, W_OK) == -1 && access(outfile, F_OK) == 0)
			return (error_exit(outfile));
		open_files(infile, outfile, pipex);
	}
	return (1);
}*/

void	open_files(char *infile, char *outfile, t_multi *pipex)
{
	pipex->inf_fd = open(infile, O_RDONLY);
	pipex->outf_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->inf_fd == -1 || pipex->outf_fd == -1)
		error_exit("open");
}


/*void	get_input_append(int fd, char *delim, char *outfile, t_multi *pipex)
{
	char	*line;
	pipex = NULL;
	outfile = NULL;
	//check for errors in Delimiter name
	while (1)
	{
		line = get_next_line(0);
		if (line == NULL)
			return;
		if (!ft_strncmp(line, delim, ft_strlen(line) - 1))
		{
			ft_printf("endoffile\n");
			free(line);
			return;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
	if (access(outfile, W_OK) == -1 && access(outfile, F_OK) == 0)
			error_exit(outfile);
	pipex->inf_fd = open("here_doc", O_RDONLY);
	pipex->outf_fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (pipex->inf_fd == -1 || pipex->outf_fd == -1)
		error_exit("open");
}*/
