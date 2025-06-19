/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontero <fmontero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:28:03 by fmontero          #+#    #+#             */
/*   Updated: 2025/06/19 09:32:30 by fmontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_cmd_data(t_cmd_data *cmd);
void	ft_free_fd_pipe(t_pipex_fds *fds);

void ft_free_fds(t_pipex_fds *fds)
{
	if (fds->in_fd >= 0)
		close(fds->in_fd);
	if (fds->out_fd >= 0)
		close(fds->out_fd);
	if (fds->pipe_fds[0] >= 0)
		close(fds->pipe_fds[0]);
	if (fds->pipe_fds[1] >= 0)
		close(fds->pipe_fds[1]);
}

void ft_free_cmd_data(t_cmd_data *cmd)
{
	free(cmd->path);
	ft_free_split(cmd->args);
}
