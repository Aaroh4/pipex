/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:05:01 by ahamalai          #+#    #+#             */
/*   Updated: 2024/03/02 14:33:09 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <fcntl.h>

typedef struct pipex
{
	int		infile;
	int		outfile;
	int		id;
	int		pid;
	int		here_doc;
	int		tube;
	int		*pipe;
	int		cmd_nbr;
	char	*path;
	char	**cmd_path;
	char	*cmd;
	char	**cmd_args;
}	t_pipex;

void	ft_error_sort(t_pipex pipex, int i);
void	ft_free_process(t_pipex pipex);
void	ft_first_child(t_pipex pipex, char **argv, char **envp);
void	ft_second_child(t_pipex pipex, char **argv, char **envp);
//void	ft_do_forking(t_pipex pipex, char **argv, char **envp, int *tube);
void	ft_do_forking(t_pipex pipex, char **argv, char **envp);
char	*ft_find_cmd(char **paths, char *cmd);
void	ft_find_outfile(t_pipex *pipex, char *argv);
void	ft_find_infile(t_pipex *pipex, char **argv);
void	ft_close_pipes(t_pipex *pipex);

#endif