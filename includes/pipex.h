/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:02:55 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/07/04 16:13:37 by hzimmerm         ###   ########.fr       */
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
}	t_multi;


//int		permissions_and_open(char *infile, char *delim, char *outfile, t_multi *pipex);
//void	get_input_append(int fd, char *delim, char *outfile, t_multi *pipex);
void	get_input_append(int fd, char **argv, char *outfile, t_multi *pipex);
int	permissions_and_open(int argc, char **argv, t_multi *pipex);

void	create_pipes(t_multi *pipex);
void	close_all_pipes(t_multi *pipex);
void	close_selected_pipes(t_multi *pipex);
void	replace_pipes(t_multi *pipex);
void	open_files(char *infile, char *outfile, t_multi *pipex);
void	wait_loop(t_multi *pipex);
int		error_return(char *message);
void	free_array(char **str);
int		child_process_bonus(char **argv, char **env, t_multi *pipex);
int		parent_process_bonus(char **argv, char **env, t_multi *pipex, int pid);
char	*find_cmd_file(char **cmd, char **env);
char	*get_paths(char **env, char *name);
int	print_exit(char *message);
int	error_exit(char *message);

#endif
