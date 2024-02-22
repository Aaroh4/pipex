/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:51:12 by ahamalai          #+#    #+#             */
/*   Updated: 2024/02/22 16:40:10 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_free_child_p(t_pipex pipex)
{
	int	i;

	i = 0;
	while (pipex.cmd_args[i])
	{
		free(pipex.cmd_args[i]);
		i++;
	}
	free(pipex.cmd_args);
	free(pipex.cmd);
}

void	ft_free_process(t_pipex pipex)
{
	int	i;

	i = 0;
	while (pipex.cmd_path[i])
	{
		free(pipex.cmd_path[i]);
		i++;
	}
	free(pipex.cmd_path);
}

void	ft_error_sort(t_pipex pipex, int i)
{
	pipex.pid1 = 1;
	if (i == 1)
		ft_printf("Error: FD failed\n");
	else if (i == 2)
		ft_printf("Error: Pipe failed\n");
	else if (i == 3)
	{
		ft_free_child_p(pipex);
		write(2, "Error: Wrong command\n", 21);
	}
	else if (i == 4)
	{
		ft_free_process(pipex);
		ft_printf("Error: Fork failed\n");
	}
	else if (i == 5)
		write(2, "Error: ft_split malloc failed\n", 30);
	exit(0);
}
