/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontero <fmontero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 13:25:44 by fmontero          #+#    #+#             */
/*   Updated: 2025/06/18 17:54:10 by fmontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_get_cmd_data(t_cmd_data	*cmd, char *argv_str, char **envp)
{
	int		status;

	cmd->args = ft_split(argv_str, ' ');
	if (cmd->args == NULL)
	{
		ft_print_error("malloc", 0);
		return (1);
	}
	cmd->path = ft_get_exec_path(cmd->args[0], envp);
	if (cmd->path == NULL)
		ft_free_split(cmd->args);
	return (status);
}

char *ft_get_exec_path(char *cmd_name, char **envp)
{
	char 	*exec_path;
	char	**paths;

	if (ft_strchr(cmd_name, '/'))
		return (cmd_name);
	paths = ft_get_paths_from_envp(envp);
	if (paths == NULL)
		return (NULL);
	exec_path = ft_find_exec_path(cmd_name, paths);
	free(paths);
	return (exec_path);
}

char	**ft_get_paths_from_envp(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			if (paths == NULL)
				ft_print_error("pipex: malloc");
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char *ft_find_exec_path(char *cmd_name, char **paths)
{
	int		i;
	char	*exec_path;
	int		permission_denied;

	i = 0;
	permission_denied = 0;
	while (paths[i] != NULL)
	{
		exec_path = ft_path_append(paths[i], cmd_name);
		if (exec_path == NULL)
			return (NULL);
		if (access(exec_path, X_OK) == 0)
			return (exec_path);
		if (errno == EACCES)
			permission_denied = 1;
		free(exec_path);
		i++;
	}
	if (permission_denied == 1)
		ft_print_error(cmd_name, PERMISSION_DENIED);
	else
		ft_print_error(cmd_name, CMD_NOTFOUND);
	return(exec_path);
}


char	*ft_path_append(char *path, char *tail)
{
	char	*res;
	char	*aux;
		
	aux = ft_strjoin(path, "/");
	if (aux == NULL && errno == ENOMEM)
		ft_print_error("pipex: malloc");
	res = ft_strjoin(aux, tail);
	if (res == NULL && errno == ENOMEM)
		ft_print_error("pipex: malloc");
	free(aux);
	return (res);
}