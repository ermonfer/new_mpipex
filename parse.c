/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontero <fmontero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 13:25:44 by fmontero          #+#    #+#             */
/*   Updated: 2025/06/15 20:41:03 by fmontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		ft_get_paths_from_envp(char ***paths, char **envp);
int 	ft_get_cmd_exec_path(char **paths, char *cmd_name, char **cmd_path);
int 	ft_get_cmds_data(t_cmd_data *cmds, int argc, char **argv, char **envp);
void	ft_free_cmds_data(t_cmd_data *cmds, int pos);

int ft_get_cmds_data(t_cmd_data *cmds, int argc, char **argv, char **envp)
{
	char	**paths;
	int		status;
	int		i;

	status = ft_get_paths_from_envp(&paths, envp);
	if (status != SUCCESS)
		return (status);
	i = 0;
	while (i < argc - 3)
	{
		cmds[i].args = ft_split(argv[i + 1], ' ');
		if (cmds[i].args == NULL)
		{
			status = MALLOC_ERROR;
			break ;
		}
		status = ft_get_cmd_exec_path(paths, cmds[i].args[0], &cmds[i].path);
		if (status != SUCCESS)
			break ;
		i++;
	}
	if (status != SUCCESS)
		ft_free_cmds_data(cmds, i);
	ft_free_split(paths);
	return (status);
}

int ft_get_cmd_exec_path(char **paths, char *cmd_name, char **cmd_path)
{
	int		i;
	char 	*path_exec;
	char 	*aux;

	i = 0;
	while (paths[i] != NULL)
	{
		aux = ft_strjoin(paths[i], "/");
		path_exec = ft_strjoin(aux, cmd_name);
		free(aux);
		if (path_exec == NULL)
			return (MALLOC_ERROR);
		if (access(path_exec, X_OK) == 0)
		{
			*cmd_path = path_exec;
			return (SUCCESS);
		}
		free(path_exec);
		i++;
	}
	ft_putstr_fd("Command not found: ", 2);
	ft_putendl_fd(cmd_name, 2);
	return(FILE_ERROR);
}

int	ft_get_paths_from_envp(char ***paths, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			*paths = ft_split(envp[i] + 5, ':');
			if (*paths == NULL)
				return (MALLOC_ERROR);
			return (SUCCESS);
		}
		i++;
	}
	return (FILE_ERROR);
}

void	ft_free_cmds_data(t_cmd_data *cmds, int pos)
{
	int	i;

	i = 0;
	while (i <= pos)
	{
		ft_free_split(cmds[i].args);
		free(cmds[i].path);
		i++;
	}	
}
