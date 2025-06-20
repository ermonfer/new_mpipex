/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontero <fmontero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:42:33 by fmontero          #+#    #+#             */
/*   Updated: 2025/06/19 19:42:04 by fmontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Global def
#ifndef PIPEX_H
# define PIPEX_H

// Libft
# include "./libft/include/libft.h"
# include "./libft/include/extra.h"

// Libs
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

// Structs
typedef struct s_pipex_fds
{
	int	in_fd;
	int	out_fd;
	int	pipe_fds[2];
}	t_pipex_fds;

typedef struct s_cmd_data
{
	char	*path;
	char	**args;
}	t_cmd_data;

// Macros
# define PERMISSION_DENIED 1
# define CMD_NOTFOUND 2

// parse.c
int	ft_get_cmd_data(t_cmd_data	*cmd, char *argv_str, char **envp);

// free.c
void	ft_free_cmd_data(t_cmd_data *cmd);
void	ft_free_fds(t_pipex_fds *fds);
void	ft_check_args_number(int argc);

#endif