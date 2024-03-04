/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:12:00 by ahamalai          #+#    #+#             */
/*   Updated: 2024/03/04 13:24:16 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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

void	ft_do_forking(t_pipex p, char **argv, char **envp)
{
	p.pid = fork();
	if (!p.pid)
	{
		if (p.id == 0 && p.here_doc == 0)
			ft_dupping(p.infile, p.pipe[1]);
		else if (p.id == 0 && p.here_doc == 1)
			ft_dupping(p.tube, p.pipe[1]);
		else if (p.id == p.cmd_nbr - 1)
			ft_dupping(p.pipe[2 * p.id - 2], p.outfile);
		else
			ft_dupping(p.pipe[2 * p.id - 2], p.pipe[2 * p.id + 1]);
		ft_close_pipes(&p);
		p.cmd_args = ft_split(argv[2 + p.here_doc + p.id], ' ');
		p.cmd = ft_find_cmd(p.cmd_path, p.cmd_args[0]);
		if (execve(p.cmd, p.cmd_args, envp) == -1)
		{
			ft_error_sort(p, 7);
			exit(1);
		}
	}
}
