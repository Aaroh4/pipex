/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:12:00 by ahamalai          #+#    #+#             */
/*   Updated: 2024/02/22 16:39:41 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_first_child(t_pipex pipex, char **argv, char **envp)
{
	dup2(pipex.tube[1], 1);
	close(pipex.tube[0]);
	dup2(pipex.infile, 0);
	pipex.cmd_args = ft_split(argv[2], ' ');
	if (!pipex.cmd_args)
		ft_error_sort(pipex, 5);
	pipex.cmd = ft_find_cmd(pipex.cmd_path, pipex.cmd_args[0]);
	if (!pipex.cmd)
		ft_error_sort(pipex, 3);
	execve(pipex.cmd, pipex.cmd_args, envp);
}

void	ft_second_child(t_pipex pipex, char **argv, char **envp)
{
	dup2(pipex.tube[0], 0);
	close(pipex.tube[1]);
	dup2(pipex.outfile, 1);
	pipex.cmd_args = ft_split(argv[3], ' ');
	if (!pipex.cmd_args)
		ft_error_sort(pipex, 5);
	pipex.cmd = ft_find_cmd(pipex.cmd_path, pipex.cmd_args[0]);
	if (!pipex.cmd)
		ft_error_sort(pipex, 3);
	execve(pipex.cmd, pipex.cmd_args, envp);
}

void	ft_do_forking(t_pipex pipex, char **argv, char **envp)
{
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		ft_error_sort(pipex, 4);
	if (pipex.pid1 == 0)
		ft_first_child(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		ft_error_sort(pipex, 4);
	if (pipex.pid2 == 0)
		ft_second_child(pipex, argv, envp);
}