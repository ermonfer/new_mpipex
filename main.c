/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontero <fmontero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:39:30 by fmontero          #+#    #+#             */
/*   Updated: 2025/06/18 17:59:42 by fmontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		execve_p(char **envp);
int 	ft_waiting_childs_return(pid_t childs[2]);
int		ft_init_pipex(t_cmd_data *cmds, int argc, char **argv, char **enpv);
int 	ft_child1_exec(t_pipex_fds fds, t_cmd_data cmds);
int		ft_open_fds(t_pipex_fds *fds, int argc, char **argv);
void	ft_check_args_number(int argc);
void	ft_check_infile_outfile(int argc, char *argv);
void	ft_child_1(t_pipex_fds *fds, t_cmd_data *cmds);
void	ft_child_2(t_pipex_fds *fds, t_cmd_data *cmds);


int	main(int argc, char *argv[], char *envp[])
{
	t_pipex_fds		fds;

	ft_check_args_number(argc);
	ft_get_cmds_data(cmds, argc, argv, envp);
	if (pipe(fds.pipe_fds) == -1)
	{
		print_errors("pipe");
		ft_free_cmds_data(cmds, 2);
		return (PIPE_ERROR);
	}


	
	/* iniciar pipe*/
	/* hacer los fork, redirecciones y execve*/
	/* esperar a los procesos y devolver el valor de retorno del 
	seguno hijo*/
	/* Imprimir los errores en el caso de haberlos*/
}

int	ft_init_pipex(t_cmd_data *cmds, int argc, char **argv, char **enpv)
{
	t_pipex_fds		*fds;
	int				pid1;
	int				pid2;

	fds = malloc(sizeof(t_pipex_fds));
	if (fds == NULL)
		return (ERR_MALLOC);
	if (ft_open_fd(fds, argc, argv) != SUCCESS)
		return (ft_free_fds(fds, j));
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

void	ft_child_1(char *argv, char *envp, t_pipex_fds *fds, t_cmd_data *cmds)
{
	close(fds->pipe_fds[1]);
	fds->in_fd = open(argv[1], O_WRONLY); 
	if (fds->in_fd == -1)
	{
		ft_print_errors(argv[1]);
		ft_free_cmds_data(cmds, 2);
		return ;
	}
	if (dup2(fds->in_fd, STDIN_FILENO) == -1)
	{
		ft_print_errors("dup2");
		ft_free_cmds_data(cmds, 2);
		close(fds->in_fd);
		return ;
	}
	close(fds->in_fd);
	if (dup2(fds->pipe_fds[1], STDOUT_FILENO) == -1)
	{
		ft_print_errors("dup2");
		ft_free_cmds_data(cmds, 2);
		close(fds->pipe_fds[1]);
		return ;
	}
	close(fds->pipe_fds[1]);
	execve(cmds[0].path, cmds[0].args, envp);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	return ;
}
