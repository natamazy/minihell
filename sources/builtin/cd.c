/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:08:47 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/20 17:39:46 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "builtin.h"
#include "minishell.h"
#include "utilities.h"

#include <stdbool.h>
#include <sys/stat.h>

int	cd(char *path, t_pipex *pipex, int *is_builtin)
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];
	char	*pwd_to_set;
	char	*modified_cmd;

	*is_builtin = 1;
	modified_cmd = NULL;
	if (!path)
	{
		modified_cmd = get_var_in_env(pipex->envp, "HOME", 1);
		if (!modified_cmd || modified_cmd == NULL
			|| (modified_cmd && modified_cmd[0] == '\0'))
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
	}
	else if (path && path[0] && path[0] == '-' && ft_strlen(path) == 1)
	{
		modified_cmd = get_var_in_env(pipex->envp, "OLDPWD", 1);
		if (!modified_cmd || modified_cmd == NULL
			|| (modified_cmd && modified_cmd[0] == '\0'))
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			return (1);
		}
	}
	else if (path && path[0] == '~')
		modified_cmd = modify_cmd(path, pipex, 0, 0);
	else
		modified_cmd = path;
	if (!file_or_directory_exists(modified_cmd))
	{
		p_err(1, "minishell: cd: ",
			modified_cmd, ": No such file or directory\n");
		if (path && path[0] == '~')
			free(modified_cmd);
		return (1);
	}
	if (!is_directory(modified_cmd))
	{
		p_err(1, "minishell: cd: ", modified_cmd, ": Not a directory\n");
		if (path && path[0] == '~')
			free(modified_cmd);
		return (1);
	}
	if (!can_access_directory(modified_cmd))
	{
		p_err(1, "minishell: cd: ", modified_cmd, ": Permission denied\n");
		if (path && path[0] == '~')
			free(modified_cmd);
		return (1);
	}
	if (chdir(modified_cmd) == -1)
	{
		p_err(1, "minishell: cd: ",
			modified_cmd, ": No such file or directory\n");
		return (1);
	}
	getcwd(old_pwd, PATH_MAX);
	pwd_to_set = NULL;
	if (check_and_export(pipex, pwd_to_set, old_pwd, 0) == 1)
		return (1);
	getcwd(new_pwd, PATH_MAX);
	free(pwd_to_set);
	if (check_and_export(pipex, pwd_to_set, new_pwd, 1) == 1)
		return (1);
	if (path && path[0] == '~')
		free(modified_cmd);
	return (0);
}
