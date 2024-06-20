/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:08:47 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/20 17:58:18 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "builtin.h"
#include "minishell.h"
#include "utilities.h"

#include <stdbool.h>
#include <sys/stat.h>

int	cd_help_1(char *path, char **modified_cmd, t_pipex *pipex)
{
	if (!path)
	{
		*modified_cmd = get_var_in_env(pipex->envp, "HOME", 1);
		if (!*modified_cmd || *modified_cmd == NULL
			|| (*modified_cmd && *modified_cmd[0] == '\0'))
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
	}
	else if (path && path[0] && path[0] == '-' && ft_strlen(path) == 1)
	{
		*modified_cmd = get_var_in_env(pipex->envp, "OLDPWD", 1);
		if (!*modified_cmd || *modified_cmd == NULL
			|| (*modified_cmd && *modified_cmd[0] == '\0'))
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			return (1);
		}
	}
	else if (path && path[0] == '~')
		*modified_cmd = modify_cmd(path, pipex, 0, 0);
	else
		*modified_cmd = path;
	return (0);
}

int	cd_help_2(char *path, char *mc)
{
	if (!file_or_directory_exists(mc))
	{
		p_err(1, "minishell: cd: ", mc, ": No such file or directory\n");
		if (path && path[0] == '~')
			free(mc);
		return (1);
	}
	if (!is_directory(mc))
	{
		p_err(1, "minishell: cd: ", mc, ": Not a directory\n");
		if (path && path[0] == '~')
			free(mc);
		return (1);
	}
	if (!can_access_directory(mc))
	{
		p_err(1, "minishell: cd: ", mc, ": Permission denied\n");
		if (path && path[0] == '~')
			free(mc);
		return (1);
	}
	if (chdir(mc) == -1)
		return (p_err(1, "minishell: cd: ", mc,
				": No such file or directory\n"), 1);
	return (0);
}

int	cd(char *path, t_pipex *pipex, int *is_builtin)
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];
	char	*pwd_to_set;
	char	*modified_cmd;

	*is_builtin = 1;
	modified_cmd = NULL;
	if (cd_help_1(path, &modified_cmd, pipex) == 1)
		return (1);
	if (cd_help_2(path, modified_cmd) == 1)
		return (1);
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
