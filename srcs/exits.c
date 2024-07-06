/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 19:32:02 by Henriette         #+#    #+#             */
/*   Updated: 2024/07/06 19:14:02 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	error_return(char *message)
{
	perror(message);
	return (0);
}

int	error_exit(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

int	print_exit(char *message)
{
	ft_putstr_fd(message, 2);
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
