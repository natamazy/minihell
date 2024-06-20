/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:09:31 by aggrigor          #+#    #+#             */
/*   Updated: 2024/06/20 17:03:59 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "utilities.h"

void	perror_exit(int err_num, t_pipex *pipex, char *msg, int exit_status)
{
	if (pipex && pipex->pipes != NULL)
	{
		free(pipex->pipes);
		pipex->pipes = NULL;
	}
	if (err_num == INVALID_ARG_CNT)
		exit(p_err(1, "Invalid count of arguments\n", NULL, NULL));
	else if (err_num == QUOT_ERR)
		q_err(exit_status, "minishell : syntax error near unexpected token `", \
		msg[0], "'\n");
	else if (err_num == MALLOC_ERR)
		exit(p_err(exit_status, "minishell: ", NULL, ": malloc error\n"));
	else if (err_num == PIPE_ERR)
		perror("pipe failed");
	else if (err_num == SYNTAX_ERR)
		p_err(exit_status, "minishell: syntax error near unexpected token `", \
		msg, "'\n");
	else if (err_num == FORK_ERR)
		perror("fork failed");
	else if (err_num == DUP_ERR)
		perror("dup failed");
	else if (err_num == CMD_NOT_FOUND)
		exit(p_err(exit_status, "minishell: ", msg, ": command not found\n"));
	else if (err_num == EXECVE_ERR)
		perror("execve failed");
}
