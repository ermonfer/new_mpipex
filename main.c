/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontero <fmontero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:39:30 by fmontero          #+#    #+#             */
/*   Updated: 2025/06/18 21:18:51 by fmontero         ###   ########.fr       */
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
		ft_print_error("pipex: pipe", 0);
		return (1);
	}
	ft_run_childs(childs, argv, envp);
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

void	ft_run_childs(t_pipex_fds fds, pid_t *childs, char **argv, char **envp)
{
	childs[0] = fork();
	if (childs[0] == -1)
		ft_print_error("pipex: fork", 0);
	if (childs[0] == 0)
		ft_child_1(fds, argv[2], envp);
	childs[1] = fork();
	if (childs[1] == -1)
		ft_print_error("pipex: fork", 0);
	if (childs[1] == 0)
		ft_child_2(fds, argv[3], envp);
}

int	execve_p(char **envp)
{
	// Comando y argumentos
    char *cmd[] = { "ls", "-l", NULL}; //Esto es como espera recibir los argumentos.

    // Ruta absoluta al ejecutable
    char *path = "/bin/ls"; //Esto es como espera recibir la dirección.

    // Ejecutar el comando
	execv(path, cmd);
    perror("execve");
	return (1);
}

void	ft_check_args_number(int argc)
{
	if (argc != 5)
	{
		ft_putstr_fd("Incorrect number of arguments\n");
		exit(1);
	}
	return ;
}

void	ft_child_1(t_pipex_fds *fds, char **argv, char  **envp)
{
	t_cmd_data cmd;

	close(fds->pipe_fds[1]);
	fds->in_fd = open(argv[1], O_WRONLY);
	if (fds->in_fd == -1)
		return ;
	if (dup2(fds->in_fd, STDIN_FILENO) == -1)
	{
		close(fds->in_fd);
		close(fds->pipe_fds[0]);
	}
	ft_get_cmd_data()
	
	



	

}

void	setup_redirections(t_pipex_fds *fds, char **argv)	
{
	fds->in_fd = open(argv[1], WR)

}