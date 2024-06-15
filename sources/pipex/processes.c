/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:13:12 by aggrigor          #+#    #+#             */
/*   Updated: 2024/06/15 22:40:52 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "minishell.h"
#include "builtin.h"

void	wait_processes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_cnt)
	{
		if (wait(NULL) == -1)
		{
			exit(EXIT_SUCCESS);
		}
		i++;
	}
}

void	create_processes(t_pipex *pipex)
{
	pid_t	pid;
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = pipex->cmds;
	while (i < pipex->cmd_cnt)
	{
		pid = fork();
		if (pid == -1)
			perror_exit(FORK_ERR, pipex);
		if (pid == 0)
		{
			dups(pipex, cmd);
			config_cmd(pipex, cmd);
			if (execve(cmd->cmd_path, cmd->cmd_args,
			env_list_to_array(pipex->envp)) == -1)
			{
				perror_exit(EXECVE_ERR, pipex);
			}
		}
		cmd = cmd->next;
		i++;
	}
	
}
