/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontero <fmontero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:42:33 by fmontero          #+#    #+#             */
/*   Updated: 2025/06/15 13:21:04 by fmontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Global def
#ifndef PIPEX_H
#define PIPEX_H

// Libft
# include "./libft/include/libft.h"

// Libs
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

// Macros for error
# define SUCCESS 0
# define MALLOC_ERROR 1
# define FILE_ERROR 2
# define PIPE_ERROR 3
# define FORK_ERROR 4

// Structs
typedef struct s_pipex_fds
{
	int	in_fd;
	int	out_fd;
	int	pipe_fds[2];
}	t_pipex_fds;

// Donde cargar los datos una vez parseado.
typedef struct s_cmds_data
{
	char	**cmd_paths;
	char	**cmd_arg[2];
}	t_cmds_data;

int	check_args(int argc);
int	check_files(char *infile, char *outfile);
int	check_cmds(t_cmds_data *cmds);

#endif