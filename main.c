/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontero <fmontero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:39:30 by fmontero          #+#    #+#             */
/*   Updated: 2025/06/19 20:30:56 by fmontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_run_childs(t_pipex_fds *fds, pid_t *childs, char **argv, char **envp);
static void	ft_child_1(t_pipex_fds *fds, char *infile, char *cmd_str, char **envp);
static void	ft_child_2(t_pipex_fds *fds, char *outfile, char *cmd_str, char **envp);
static void	redirections(t_pipex_fds *fds, int in_fd, int out_fd);

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex_fds		fds;
	pid_t			childs[2];
	int				status;

	ft_check_args_number(argc);
	fds = (t_pipex_fds){-1, -1, {-1, -1}};
	if (pipe(fds.pipe_fds) == -1)
	{
		perror("pipex: pipe");
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
		perror("pipex: fork");
	if (childs[0] == 0)
		ft_child_1(fds, argv[1], argv[2], envp);
	childs[1] = fork();
	if (childs[1] == -1)
		perror("pipex: fork");
	if (childs[1] == 0)
		ft_child_2(fds, argv[4], argv[3], envp);
}


void	ft_child_1(t_pipex_fds *fds, char *infile, char *cmd_str, char **envp)
{
	t_cmd_data	cmd;

	close(fds->pipe_fds[0]);
	fds->in_fd = open(infile, O_RDONLY);
	if (fds->in_fd == -1)
	{
		perror("infile");
		exit(1);
	}
	redirections(fds, fds->in_fd, fds->pipe_fds[1]);
	if (ft_get_cmd_data(&cmd, cmd_str, envp) == 0)
	{
		execve(cmd.path, cmd.args, envp);
		perror("pipex: execve");
		ft_free_cmd_data(&cmd);
	}
	ft_free_fds(fds);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(1);
}

void	ft_child_2(t_pipex_fds *fds, char *outfile, char *cmd_str, char **envp)
{
	t_cmd_data	cmd;

	close(fds->pipe_fds[1]);
	fds->out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fds->out_fd == -1)
	{
		perror("pipex: open");
		exit (1);
	}
	redirections(fds, fds->pipe_fds[0], fds->out_fd);
	if (ft_get_cmd_data(&cmd, cmd_str, envp) == 0)
	{
		execve(cmd.path, cmd.args, envp);
		perror("pipex: execve");
		ft_free_cmd_data(&cmd);
	}
	ft_free_fds(fds);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(1);
}

void	redirections(t_pipex_fds *fds, int in_fd, int out_fd)
{
	if (dup2(in_fd, STDIN_FILENO) == -1)
	{
		perror("pipex: dup2");
		ft_free_fds(fds);
		exit(1);
	}
	close(in_fd);
	if (dup2(out_fd, STDOUT_FILENO) == -1)
	{
		perror("pipex: dup2");
		ft_free_fds(fds);
		exit(1);
	}
	close(out_fd);
}
