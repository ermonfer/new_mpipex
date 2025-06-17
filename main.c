/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontero <fmontero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:39:30 by fmontero          #+#    #+#             */
/*   Updated: 2025/06/17 00:09:29 by fmontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execve_p(char **envp);
int ft_waiting_childs_return(pid_t childs[2]);
int	ft_init_pipex(t_cmd_data *cmds, int argc, char **argv, char **enpv);
int ft_child1_exec(t_pipex_fds fds, t_cmd_data cmds);
int	ft_open_fds(t_pipex_fds *fds, int argc, char **argv);

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex_fds		*fds;
	pid_t			childs[2];

	
	//comprobaciones de que todo sea accesible
	//parseo de argumentos
	// comprobar el infile y el outfile y el número de args.

	
	//ft_open_fds()
	childs[1] = fork();
	if (childs[0] == -1)
	{
		perror("fork 1");
		//free todo
	}

	if (childs[0] == 0)
		// run_child_1

	childs[2] = fork();
	if (childs[1] == -1)
	{
		perror("fork 2");
	}

	if (childs[1] == 1)
		// run_child_2

	return (ft_waiting_childs_return(childs));
}

int	ft_init_pipex(t_cmd_data *cmds, int argc, char **argv, char **enpv)
{
	t_pipex_fds		*fds;
	int				pid1;
	int				pid2;

	fds = malloc(sizeof(t_pipex_fds));
	if (fds == NULL)
		return (MALLOC_ERROR);
	if (ft_open_fd(fds, argc, argv) != SUCCESS)
		return (ft_free_fds(fds, FILE_ERROR));
	pid1 = fork();
	if (pid1 < 0)
		return (ft_free_fds (fds, FORK_ERROR));
	if (pid1 == 0)
		ft_child_1(cmds, fds, enpv);
	pid2 = fork ();
	if (pid2 < 0)
		return (ft_free_fds (fds, FORK_ERROR));
	if (pid2 == 0)
		ft_child_2(cmds, fds, enpv);
	ft_free_fds(fds, SUCCESS);
	//waitpid(pid1, NULL, 0);
	//waitpid(pid2, NULL, 0);
	return (SUCCESS);
}


int	ft_open_fds(t_pipex_fds *fds, int argc, char **argv)
{
	fds->in_fd = open(argv[1], O_RDONLY);
	fds->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fds->in_fd < 0)
		perror("Error opening infile");
	if (fds->out_fd < 0)
		return (FILE_ERROR);
	if (pipe(fds->pipe_fds) == -1)
		return (PIPE_ERROR);
	return (SUCCESS);
}

int ft_waiting_childs_return(pid_t childs[2])
{
	int status;

	waitpid(childs[0], NULL, 0);
	waitpid(childs[1], &status, 0);
	if (WIFEXITED(status))
		return WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		return 128 + WTERMSIG(status);
	else
		return 1;
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
