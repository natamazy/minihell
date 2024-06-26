/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:09:31 by aggrigor          #+#    #+#             */
/*   Updated: 2024/06/20 17:20:10 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "utilities.h"

extern int	g_exit_status;

char	*find_cmd_in_paths(char *cmd_name, char **paths)
{
	char	*cmd_path;
	char	*path_with_slash;
	int		i;

	path_with_slash = join("/", cmd_name);
	if (path_with_slash == NULL)
		return (NULL);
	i = 0;
	cmd_path = cmd_name;
	while (paths && paths[i])
	{
		cmd_path = join(paths[i], path_with_slash);
		if (cmd_path == NULL)
			break ;
		if (access(cmd_path, F_OK) == 0 && access(cmd_path, X_OK) == 0)
			break ;
		free(cmd_path);
		cmd_path = cmd_name;
		i++;
	}
	free(path_with_slash);
	path_with_slash = NULL;
	return (cmd_path);
}

char	*get_cmd_path(char *cmd_name, char **paths, t_pipex *pipex)
{
	char	*cmd_path;

	cmd_path = NULL;
	if (access(cmd_name, F_OK) == 0 && access(cmd_name, X_OK) == 0)
		cmd_path = cmd_name;
	else
	{
		cmd_path = find_cmd_in_paths(cmd_name, paths);
		if (cmd_path == NULL)
			perror_exit(MALLOC_ERR, pipex, NULL, 1);
		else if (cmd_path == cmd_name)
			perror_exit(CMD_NOT_FOUND, pipex, cmd_path, 127);
	}
	free_matrix(paths);
	paths = NULL;
	return (cmd_path);
}

void	config_cmd(t_pipex *pipex, t_cmd *cmd)
{
	char	**paths;
	char	*var;

	if (cmd->cmd_path && cmd->cmd_path[0] == '\0')
		perror_exit(CMD_NOT_FOUND, pipex, cmd->cmd_path, 127);
	var = get_var_in_env(pipex->envp, "PATH", 1);
	paths = ft_split(var, ':');
	free(var);
	cmd->cmd_path = get_cmd_path(cmd->cmd_path, paths, pipex);
}

int	q_err(int exit_status, char *s1, char s2, char *s3)
{
	global(exit_status, 1);
	g_exit_status = exit_status;
	if (s1 != NULL)
		ft_putstr_fd(s1, 2);
	write(2, &s2, 1);
	if (s3 != NULL)
		ft_putstr_fd(s3, 2);
	return (exit_status);
}

int	p_err(int exit_status, char *s1, char *s2, char *s3)
{
	global(exit_status, 1);
	g_exit_status = exit_status;
	if (s1 != NULL)
		ft_putstr_fd(s1, 2);
	if (s2 != NULL)
		ft_putstr_fd(s2, 2);
	if (s3 != NULL)
		ft_putstr_fd(s3, 2);
	return (exit_status);
}
