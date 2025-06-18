/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontero <fmontero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 13:25:44 by fmontero          #+#    #+#             */
/*   Updated: 2025/06/18 14:43:55 by fmontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_get_cmd_data(t_cmd_data	*cmd, char *argv_str, char **envp)
{
	int		status;

	cmd->args = ft_split(argv_str, ' ');
	if (cmd->args == NULL)
		ft_print_error("pipex: malloc");
	


	return (status);
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

char *ft_get_exec_path(char *cmd_name, char **envp)
{
	int		i;
	char 	*exec_path;
	char	**paths;
	int		status;
	int		permission_denied;

	if (ft_strchr(cmd_name, '/'))
		return (cmd_name);
	paths = ft_get_paths_from_envp(envp);
	if (paths == NULL)
		return (NULL);
	permission_denied = 0;
	i = -1;
	while (paths[++i] != NULL)
	{
		exec_path = ft_path_append(paths[i], cmd_name);
		if (exec_path == NULL)
			break ;
		status = access(exec_path, X_OK);
		if (status == 0)
			break ;
		if (errno == EACCES)
			permission_denied = 1;
		free(exec_path);
	}
	free(paths);
	if (permission_denied == 1)
		ft_print_error(); //permiso denegado
	else
		ft_print_error(); //comando no encontrado
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