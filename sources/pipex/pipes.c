/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:10:06 by aggrigor          #+#    #+#             */
/*   Updated: 2024/06/17 11:54:05 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "minishell.h"

void	init_pipes(t_pipex *pipex)
{
	int		i;
	t_cmd	*cur;

	pipex->pipes = malloc(sizeof(int [2]) * (pipex->cmd_cnt - 1));
	if (pipex->pipes == NULL)
		perror_exit(MALLOC_ERR, pipex);
	i = 0;
	cur = pipex->cmds;
	while (i < pipex->cmd_cnt - 1)
	{
		if (pipe(pipex->pipes[i]) == -1)
			perror_exit(PIPE_ERR, pipex);
		if (cur->output == 1)
			cur->output = pipex->pipes[i][1];
		if (cur->next && cur->next->input == 0)
			cur->next->input = pipex->pipes[i][0];
		cur = cur->next;
		i++;
	}
}

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_cnt - 1)
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
		i++;
	}
}

void	dups(t_pipex *pipex, t_cmd *cmd)
{
	if (cmd->input != 0)
	{
		if (dup2(cmd->input, 0) == -1)
			perror_exit(DUP_ERR, pipex);
	}
	if (cmd->output != 1)
	{
		if (dup2(cmd->output, 1) == -1)
			perror_exit(DUP_ERR, pipex);
	}
	close_pipes(pipex);
}
