/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:13:12 by aggrigor          #+#    #+#             */
/*   Updated: 2024/06/19 13:39:26 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "minishell.h"
#include "utilities.h"
#include "builtin.h"

extern int g_exit_status;

void	wait_processes(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->cmd_cnt == 1 && is_builtin(pipex->cmds->cmd_path) == 1)
		return ;
	while (i < pipex->cmd_cnt)
	{
		if (wait(NULL) == -1)
		{
			printf("OOOOOO\n");
			exit(EXIT_SUCCESS);
		}
		i++;
	}
}

void	run_builtins(t_pipex *pipex, t_cmd *cmd, int *is_builtin, int is_in_fork)
{
	if (ft_strcmp(cmd->cmd_path, "env") == 0)
		print_env(pipex->envp, is_builtin);
	else if (ft_strcmp(cmd->cmd_path, "pwd") == 0)
		pwd(cmd->output, is_builtin);
	else if (ft_strcmp(cmd->cmd_path, "cd") == 0)
		cd(pipex->cmds->cmd_args[1], pipex, is_builtin);
	else if (ft_strcmp(cmd->cmd_path, "echo") == 0)
		echo(cmd->cmd_args, cmd->output, is_builtin);
	// to be continued
	//export
	//unset

	if (*is_builtin == 1 && is_in_fork == 1)
		exit(g_exit_status);
}

void	run_standard_mode(t_pipex *pipex, t_cmd *cmd)
{
	pid_t	pid;
	int		is_builtin;

	pid = fork();
	if (pid == -1)
		perror_exit(FORK_ERR, pipex);
	if (pid == 0)
	{
		is_builtin = 0;
		dups(pipex, cmd);
		run_builtins(pipex, cmd, &is_builtin, 1);
		if (is_builtin == 0)
		{
			config_cmd(pipex, cmd);
			if (execve(cmd->cmd_path, cmd->cmd_args,
					env_list_to_array(pipex->envp)) == -1)
				perror_exit(EXECVE_ERR, pipex);
		}
	}	
}

void	create_processes(t_pipex *pipex)
{
	int		i;
	t_cmd	*cmd;
	int		is_builtin;

	i = 0;
	cmd = pipex->cmds;
	while (i < pipex->cmd_cnt)
	{
		is_builtin = 0;
		if (pipex->cmd_cnt == 1)
			run_builtins(pipex, cmd, &is_builtin, 0);
		if (is_builtin == 0)
			run_standard_mode(pipex, cmd);
		printf("cmd '%s' input - %d, output - %d\n", cmd->cmd_path, cmd->input, cmd->output);
		cmd = cmd->next;
		i++;
	}
}
