/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:39:28 by aggrigor          #+#    #+#             */
/*   Updated: 2024/06/17 12:10:38 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// write, read, close, access, dup, dup2, execve, fork, pipe, unlink,
# include <unistd.h>
// open
# include <fcntl.h>
// malloc, free, exit
# include <stdlib.h>
// perror
# include <stdio.h>
// strerror
# include <string.h>
// wait, waitpid
# include <sys/wait.h>
// for errno
# include <sys/errno.h>
// minishell
# include "minishell.h"

# define MIN_ARGS 4
// CUSTOM ERRORS
# define INVALID_ARG_CNT 1
# define FILEOUT_ERR 2
# define FILEIN_ERR 3
# define JOIN_ERR 4
# define MALLOC_ERR 5
# define PIPE_ERR 6
# define FORK_ERR 7
# define DUP_ERR 8
# define CMD_NOT_FOUND 9
# define EXECVE_ERR 10

typedef struct s_pipex
{
	int			(*pipes)[2];
	int			cmd_cnt;
	t_cmd		*cmds;
	t_env_elem	*envp;
}	t_pipex;

int		run_cmds(t_shell *shell);

//pipes.c
void	init_pipes(t_pipex *pipex);
void	close_pipes(t_pipex *pipex);
void	dups(t_pipex *pipex, t_cmd *cmd);

//processes.c
void	wait_processes(t_pipex *pipex);
void	create_processes(t_pipex *pipex);

//pipex_utils1.c
char	*find_cmd_in_paths(char *cmd_name, char **paths);
char	*get_cmd_path(char *cmd_name, char **paths, t_pipex *pipex);
void	config_cmd(t_pipex *pipex, t_cmd *cmd);
void	perror_exit(int err_num, t_pipex *pipex);

#endif