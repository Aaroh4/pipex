/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:05:51 by ahamalai          #+#    #+#             */
/*   Updated: 2024/03/04 13:23:40 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*ft_find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	ft_open_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_nbr)
	{
		if (pipe(pipex->pipe + 2 * i) < 0)
			ft_error_sort(*pipex, 2);
		i++;
	}
}

void	ft_close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_nbr)
	{
		close(pipex->pipe[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
	{
		write(2, "Error: Wrong amount of arguments\n", 33);
		exit(1);
	}
	ft_memset(&pipex, 0, sizeof(pipex));
	ft_find_infile(&pipex, argv);
	ft_find_outfile(&pipex, argv[argc - 1]);
	pipex.cmd_nbr = argc - 3 - pipex.here_doc;
	pipex.pipe = malloc(sizeof(int) * (pipex.cmd_nbr * 2));
	if (!pipex.pipe)
		ft_error_sort(pipex, 6);
	pipex.path = ft_find_path(envp);
	pipex.cmd_path = ft_split(pipex.path, ':');
	if (!pipex.cmd_path)
		ft_error_sort(pipex, 5);
	ft_open_pipes(&pipex);
	pipex.id = -1;
	while (++(pipex.id) < pipex.cmd_nbr)
		ft_do_forking(pipex, argv, envp);
	waitpid(-1, NULL, 0);
	ft_free_process(pipex);
}
