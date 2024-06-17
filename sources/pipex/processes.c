/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:13:12 by aggrigor          #+#    #+#             */
/*   Updated: 2024/06/17 12:08:17 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "minishell.h"
#include "utilities.h"
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

int	run_builtins(t_env_elem *envp, t_cmd *cmd)
{
	int	is_builtin;

	is_builtin = 0;
	if (ft_strcmp(cmd->cmd_path, "env") == 0)
		print_env(envp, &is_builtin);
	else if (ft_strcmp(cmd->cmd_path, "pwd") == 0)
		pwd(cmd->output, &is_builtin);
	// else if (ft_strcmp(cmd->cmd_path, "export" == 0)
	// to be continued
	if (is_builtin == 1)
		exit(0);
	return (0);
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
			run_builtins(pipex->envp, cmd);
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
