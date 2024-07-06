/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:02:55 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/07/06 19:13:40 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../srcs/libft/libft.h"

typedef struct s_multi
{
	int	cmd_qty;
	int	cmd_i;
	int	pipe_fd[2][2];
	int	inf_fd;
	int	outf_fd;
	int	curr;
	int	prev;
	int	here_doc;
}	t_multi;

/* execution */
int		child_process_bonus(char **argv, char **env, t_multi *pipex);
char	*find_cmd_file(char **cmd, char **env);
char	*get_paths(char **env, char *name);
int		find_command(char **argv, t_multi *pipex, char **cmd_file, char ***cmd);

/* files */
void	get_input_append(int fd, char **argv, char *outfile, t_multi *pipex);
int		permissions_and_open(int argc, char **argv, t_multi *pipex);
void	open_files(char *infile, char *outfile, t_multi *pipex);
int		is_heredoc(char **argv, t_multi *pipex);
void	remove_heredoc(t_multi *pipex, char **env);
void	remove_delimiter(char **argv);

/* pipes */
void	create_pipes(t_multi *pipex);
void	close_all_pipes(t_multi *pipex);
void	close_selected_pipes(t_multi *pipex);
void	replace_pipes(t_multi *pipex);

/* utils */
void	wait_loop(t_multi *pipex);
int		error_return(char *message);
void	free_array(char **str);
int		print_exit(char *message);
int		error_exit(char *message);
char	*ft_trim(char *line, char c);

#endif
