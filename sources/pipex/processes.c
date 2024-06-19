/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:13:12 by aggrigor          #+#    #+#             */
/*   Updated: 2024/06/19 20:44:30 by natamazy         ###   ########.fr       */
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
		g_exit_status = print_env(pipex->envp, is_builtin);
	else if (ft_strcmp(cmd->cmd_path, "pwd") == 0)
		g_exit_status = pwd(STDOUT_FILENO, is_builtin);
	else if (ft_strcmp(cmd->cmd_path, "cd") == 0)
		g_exit_status = cd(pipex->cmds->cmd_args[1], pipex, is_builtin);
	else if (ft_strcmp(cmd->cmd_path, "echo") == 0)
		g_exit_status = echo(cmd->cmd_args, STDOUT_FILENO, is_builtin);
	else if (ft_strcmp(cmd->cmd_path, "export") == 0)
		g_exit_status = export(pipex, cmd, is_builtin);
	else if (ft_strcmp(cmd->cmd_path, "unset") == 0)
		g_exit_status = unset(pipex, cmd, is_builtin);
	else if (ft_strcmp(cmd->cmd_path, "exit") == 0)
		built_exit(cmd, is_builtin, is_in_fork, 0);
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
		cmd = cmd->next;
		i++;
	}
}
