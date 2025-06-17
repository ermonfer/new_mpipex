/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontero <fmontero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:28:03 by fmontero          #+#    #+#             */
/*   Updated: 2025/06/17 19:11:06 by fmontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_cmds_data(t_cmd_data *cmds, int pos);
int		ft_free_fd_pipe(t_pipex_fds *fds, int flag);

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

void	ft_free_cmds_data(t_cmd_data *cmds, int pos)
{
	int	i;

	if (cmds == NULL)
		return ;
	i = 0;
	while (i <= pos)
	{
		ft_free_split(cmds[i].args);
		free(cmds[i].path);
		i++;
	}	
}
