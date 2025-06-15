/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontero <fmontero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:42:33 by fmontero          #+#    #+#             */
/*   Updated: 2025/06/15 19:10:07 by fmontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Global def
#ifndef PIPEX_H
#define PIPEX_H

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
typedef struct s_cmd_data
{
	char	**path;
	char	**args;
}	t_cmd_data;

int	check_args(int argc);
int	check_files(char *infile, char *outfile);
int	check_cmds(t_cmd_data *cmds);

#endif