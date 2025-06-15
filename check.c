/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontero <fmontero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 20:54:26 by fmontero          #+#    #+#             */
/*   Updated: 2025/06/15 13:09:46 by fmontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_check_args(int argc);
int		ft_check_files(char *infile, char *outfile);
int		ft_check_cmds(t_cmds_data *cmds);
int		ft_free_fd_pipe(t_pipex_fds *fds, int flag);

void ft_check_args(int argc)
{
	if (argc != 5)
	{
		ft_putstr_fd("Incorrect number of arguments", 2);
		exit(1);
	}
}

int	check_files(const char *infile, const char *outfile)
{
	if (access(infile, R_OK) == -1)
	{
		perror("infile");
		exit(FILE_ERROR);
	}

	if (access(outfile, F_OK) == 0 && access(outfile, W_OK) == -1)
	{
		perror("outfile");
		exit(FILE_ERROR);
	}
}


int	ft_free_fd_pipe(t_pipex_fds *fds, int flag)
{
	if (fds->in_fd >= 0)
		close(fds->in_fd);
	if (fds->out_fd >= 0)
		close(fds->out_fd);
	if (fds->pipe_fds[0] >= 0)
		close(fds->pipe_fds[0]);
	if (fds->pipe_fds[1] >= 0)
		close(fds->pipe_fds[1]);
	free(fds);
	return (flag);
}