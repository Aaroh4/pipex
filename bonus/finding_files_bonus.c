/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finding_files_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:39:36 by ahamalai          #+#    #+#             */
/*   Updated: 2024/03/04 12:28:37 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	ft_here_doc(char *argv)
{
	char	*buf;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
	{
		write(2, "Error: Pipe failed\n", 19);
		exit(1);
	}
	buf = NULL;
	while (1)
	{
		write(1, "Pipe heredoc> ", 15);
		buf = get_next_line(0);
		if (!buf)
			exit(1);
		if (!ft_strncmp(argv, buf, ft_strlen(buf) - 1))
			break ;
		ft_putstr_fd(buf, pipe_fd[1]);
		free(buf);
	}
	free(buf);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

void	ft_find_infile(t_pipex *pipex, char **argv)
{
	if (!ft_strncmp("here_doc", argv[1], 9))
	{
		pipex->here_doc = 1;
		pipex->tube = ft_here_doc(argv[2]);
	}
	else
	{
		pipex->here_doc = 0;
		pipex->infile = open(argv[1], O_RDONLY);
		if (pipex->infile == -1)
			ft_error_sort(*pipex, 1);
	}
}

void	ft_find_outfile(t_pipex *pipex, char *argv)
{
	if (pipex->here_doc)
		pipex->outfile = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0000644);
	else
		pipex->outfile = open(argv, O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (pipex->outfile == -1)
		ft_error_sort(*pipex, 1);
}
