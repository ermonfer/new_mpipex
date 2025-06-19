/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontero <fmontero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:39:30 by fmontero          #+#    #+#             */
/*   Updated: 2025/06/19 17:23:55 by fmontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex_fds		fds;
	pid_t			childs[2];
	int				status;

	ft_check_args_number(argc);
	if (pipe(fds.pipe_fds) == -1)
	{
		ft_print_error("pipex: pipe");
		return (1);
	}
	ft_run_childs(&fds, childs, argv, envp);
	close(fds.pipe_fds[0]);
	close(fds.pipe_fds[1]);
	if (childs[0] != -1)
		waitpid(childs[0], NULL, 0);
	if (childs[1] != -1)
	{
		waitpid(childs[1], &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (1);
}

void	ft_run_childs(t_pipex_fds *fds, pid_t *childs, char **argv, char **envp)
{
	childs[0] = fork();
	if (childs[0] == -1)
		ft_print_error("pipex: fork");
	if (childs[0] == 0)
		ft_child_1(fds, argv[1], argv[2], envp);
	childs[1] = fork();
	if (childs[1] == -1)
		ft_print_error("pipex: fork");
	if (childs[1] == 0)
		ft_child_2(fds, argv[4], argv[3], envp);
}

void	ft_check_args_number(int argc)
{
	if (argc != 5)
	{
		ft_putstr_fd("Incorrect number of arguments\n", 2);
		exit(1);
	}
	return ;
}

void	ft_child_1(t_pipex_fds *fds, char *infile, char *cmd_str, char  **envp)
{
	t_cmd_data cmd;

	close(fds->pipe_fds[0]);
	fds->in_fd = open(infile, O_WRONLY);
	if (fds->in_fd == -1)
		return ;
	if (dup2(fds->in_fd, STDIN_FILENO) == -1)
	{
		ft_free_fds(fds);
		return ;
	}
	close(fds->in_fd);
	if (dup2(fds->pipe_fds[1], STDOUT_FILENO) == -1)
	{
		ft_free_fds(fds);
		return ;
	}
	close(fds->out_fd);
	ft_get_cmd_data(&cmd, cmd_str, envp);
	execve(cmd.path, cmd.args, envp);
	ft_print_error("execve");
	ft_free_cmd_data(&cmd);
	ft_free_fds(fds);
}

void	ft_child_2(t_pipex_fds *fds, char *outfile, char *cmd_str, char  **envp)
{
	t_cmd_data cmd;

	close(fds->pipe_fds[1]);
	fds->out_fd = open(outfile, O_RDONLY);
	if (fds->out_fd == -1)
		return ;
	if (dup2(fds->out_fd, STDOUT_FILENO) == -1)
	{
		ft_free_fds(fds);
		return ;
	}
	close(fds->out_fd);
	if (dup2(fds->pipe_fds[0], STDIN_FILENO) == -1)
	{
		ft_free_fds(fds);
		return ;
	}
	close(fds->out_fd);
	ft_get_cmd_data(&cmd, cmd_str, envp);
	execve(cmd.path, cmd.args, envp);
	ft_print_error("execve");
	ft_free_cmd_data(&cmd);
	ft_free_fds(fds);
}
