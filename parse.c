/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontero <fmontero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 13:25:44 by fmontero          #+#    #+#             */
/*   Updated: 2025/06/15 13:40:19 by fmontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_find_path(char **envp);
int	ft_get_path(t_cmds_data *cmds, char **envp);

int	ft_get_path(t_cmds_data *cmd, char **envp)
{
	char	*path_envp;

	path_envp = ft_find_path(envp);
	if (path_envp == NULL)
		return (FILE_ERROR);
	cmd->cmd_paths = ft_split(path_envp, ':');
	if (!cmd->cmd_paths)
		return (MALLOC_ERROR);
	return (SUCCESS);
}

char	*ft_find_path(char **envp)
{
	while (*envp != NULL)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}
