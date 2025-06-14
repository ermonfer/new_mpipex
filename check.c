/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontero <fmontero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 20:54:26 by fmontero          #+#    #+#             */
/*   Updated: 2025/06/14 21:42:27 by fmontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_check_args(int argc);
int		ft_check_files(char *infile, char *outfile);
int		ft_check_cmds(t_cmds_data *cmds);

void ft_check_args(int argc)
{
	if (argc != 5)
	{
		ft_putstr_fd("Incorrect number of arguments", 2);
		exit (1);
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