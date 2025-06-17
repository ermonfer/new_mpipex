/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontero <fmontero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 13:25:44 by fmontero          #+#    #+#             */
/*   Updated: 2025/06/17 20:11:53 by fmontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		ft_get_paths_from_envp(char ***paths, char **envp);
int 	ft_get_cmd_exec_path(char **paths, char *cmd_name, char **cmd_path);
int 	ft_get_cmds_data(t_cmd_data *cmds, int argc, char **argv, char **envp);
void	ft_free_cmds_data(t_cmd_data *cmds, int pos);
int		ft_get_cmd_args(int cmd_number, char ***args, char **argv);
int		ft_check_absolute_path(char *cmd_name, char **cmd_path);
char	*ft_path_append(char *path, char *tail);

int ft_get_cmds_data(t_cmd_data *cmds, int argc, char **argv, char **envp)
{
	char	**paths;
	int		status;
	int		i;

	if (ft_get_paths_from_envp(&paths, envp) == ERR_MALLOC)
		return (ERR_MALLOC);
	i = 0;
	while (i < argc - 3)
	{
		status = ft_get_cmd_args(i, &(cmds[i].args), argv);
		if (status != SUCCESS)
			break ;
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

	if (ft_strchr(cmd_name, '/'))
		return (ft_check_absolute_path(cmd_name, cmd_path));
	if (paths != NULL)
	{
		i = 0;
		while (paths[i] != NULL)
		{
			path_exec = ft_path_append(paths[i], cmd_name);
			if (path_exec == NULL)
				return (ERR_MALLOC);
			if (access(path_exec, X_OK) == 0)
			{
				*cmd_path = path_exec;
				return (SUCCESS);
			}
			free(path_exec);
			i++;
		}
	}
	return(ERR_CMD_NOTFOUND);
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
				return (ERR_MALLOC);
			return (SUCCESS);
		}
		i++;
	}
	*paths = NULL;
	return (NO_PATH_VAR_FOUND);
}

int		ft_get_cmd_args(int cmd_number, char ***args, char **argv)
{
	*args = ft_split(argv[cmd_number + 2], ' ');
	if (*args == NULL)
		return (ERR_MALLOC);
	if ((*args)[0] == NULL)
		return (ERR_CMD_NOTFOUND);
	return (SUCCESS);
}

int		ft_check_absolute_path(char *cmd_name, char **cmd_path)
{
	if (access(cmd_name, X_OK) == 0)
	{
		*cmd_path = ft_strdup(cmd_name);
		if (*cmd_path == NULL)
			return (ERR_MALLOC);
		return (SUCCESS);
	}
	return (ERR_CMD_NOTFOUND);
}

char	*ft_path_append(char *path, char *tail)
{
	char	*res;
	char	*aux;
		
	aux = ft_strjoin(path, "/");
	res = ft_strjoin(aux, tail);
	free(aux);
	return (res);
}