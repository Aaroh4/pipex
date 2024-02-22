/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:05:51 by ahamalai          #+#    #+#             */
/*   Updated: 2024/02/22 16:45:40 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <unistd.h>
#include <stdlib.h>
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

char	*ft_find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
	{
		ft_printf("Error: Wrong amount of arguments\n");
		exit(0);
	}
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile == -1)
		ft_error_sort(pipex, 1);
	pipex.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex.outfile == -1)
		ft_error_sort(pipex, 1);
	if (pipe(pipex.tube) < 0)
		ft_error_sort(pipex, 2);
	pipex.path = ft_find_path(envp);
	pipex.cmd_path = ft_split(pipex.path, ':');
	if (!pipex.cmd_path)
		ft_error_sort(pipex, 5);
	ft_do_forking(pipex, argv, envp);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	ft_free_process(pipex);
}
