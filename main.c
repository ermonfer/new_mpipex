/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontero <fmontero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:39:30 by fmontero          #+#    #+#             */
/*   Updated: 2025/06/18 19:50:10 by fmontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		execve_p(char **envp);
int 	ft_waiting_childs_return(pid_t childs[2]);
int		ft_init_pipex(t_cmd_data *cmds, int argc, char **argv, char **enpv);
int		ft_init_pipex();
int 	ft_child1_exec(t_pipex_fds fds, t_cmd_data cmds);
int		ft_open_fds(t_pipex_fds *fds, int argc, char **argv);
void	ft_check_args_number(int argc);
void	ft_check_infile_outfile(int argc, char *argv);
void	ft_child_1(char *cmd_str, char **envp);
void	ft_child_2(char *cmd_str, char **envp);


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
	childs[0] = fork();
	if (childs[0] == -1)
		ft_print_error("pipex: fork", 0);
	if (childs[0] == 0)
		ft_child_1(argv[2], envp);
	childs[1] = fork();
	if (childs[1] == -1)
		ft_print_error("pipex: fork", 0);
	if (childs[1] == 0)
		ft_child_2(argv[3], envp);
	close(fds.pipe_fds[0]);
	close(fds.pipe_fds[1]);
	if (childs[0] != -1)
		waitpid(childs[0], NULL, 0);
	if (childs[1] != -1)
		waitpid(childs[1], NULL, 0);
	return (status);
	}


	
	/* iniciar pipe*/
	/* hacer los fork, redirecciones y execve*/
	/* esperar a los procesos y devolver el valor de retorno del 
	seguno hijo*/
	/* Imprimir los errores en el caso de haberlos*/
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
