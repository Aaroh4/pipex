/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:12:00 by ahamalai          #+#    #+#             */
/*   Updated: 2024/03/03 13:39:49 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include <stdio.h>

char	*ft_find_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*cmd_path;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(cmd_path, 0) == 0)
			return (cmd_path);
		free(cmd_path);
		paths++;
	}
	return (NULL);
}

void	ft_dupping(int a, int b)
{
	dup2(a, 0);
	dup2(b, 1);
}

void	ft_do_forking(t_pipex pipex, char **argv, char **envp)
{
	pid_t pid;
	write(1, "9\n", 2);
	pid = fork();

	if (!pid)
	{
		write(1, "8\n", 2);
		if (pipex.id == 0)
		{
			write(2, "48\n", 3);
			ft_dupping(pipex.infile, pipex.pipe[1]);
		}
		else if (pipex.id == pipex.cmd_nbr - 1)
		{
			write(2, "49\n", 3);
			ft_dupping(pipex.pipe[2 * pipex.id - 2], pipex.outfile);
		}
		else
		{
			write(2, "50\n", 3);
			ft_dupping(pipex.pipe[2 * pipex.id - 2], pipex.pipe[2 * pipex.id + 1]);
		}
		ft_close_pipes(&pipex);
		pipex.cmd_args = ft_split(argv[2 + pipex.here_doc + pipex.id], ' ');
		pipex.cmd = ft_find_cmd(pipex.cmd_path, pipex.cmd_args[0]);
		if (!pipex.cmd)
		{
			write(2, "abc", 3);
			//child_free(&pipex);
			exit(1);
		} 
		if (execve(pipex.cmd, pipex.cmd_args, envp) == -1)
			exit(1);
		perror("execve");
	}
}


/*
void	ft_do_forking(t_pipex pipex, char **argv, char **envp, int *tube)
{
	write(2, "9\n", 2);
	if (*tube == 54)
		write(1, "hello", 5);
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		ft_error_sort(pipex, 4);
	else  if (!pipex.pid1)
	{
		write(2, "8\n", 2);
		if (pipex.here_doc == 0)
		{
			ft_putnbr_fd(pipex.cmd_nbr, 2);
			ft_putnbr_fd(pipex.id, 2);
			if (pipex.id == 0)
			{
				write(2, "hello32\n", 8);
				ft_dupping(pipex.infile, pipex.pipe[1]);
			}
			else if (pipex.id == pipex.cmd_nbr)
			{
				write(2, "hello33\n", 8);
				ft_dupping(pipex.pipe[2 * pipex.id - 2], pipex.outfile);
			}
			else
			{
				write(2, "hello34\n", 8);
				ft_dupping(pipex.pipe[2 * pipex.id - 2], pipex.pipe[2 * pipex.id + 1]);
			}
		}
		ft_close_pipes(&pipex);
		pipex.cmd_args = ft_split(argv[2 + pipex.here_doc + pipex.id], ' ');
		pipex.cmd = ft_find_cmd(pipex.cmd_path, pipex.cmd_args[0]);
		if (!pipex.cmd)
		{
			write(1, "Hello2", 6);
			exit(1);
		}
		execve(pipex.cmd, pipex.cmd_args, envp);
	} 
} */
