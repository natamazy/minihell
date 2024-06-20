/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:08:47 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/20 13:20:32 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "builtin.h"
#include "minishell.h"
#include "utilities.h"

#include <stdbool.h>
#include <sys/stat.h>

bool	is_directory(const char	*path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (false);
	return (S_ISDIR(path_stat.st_mode));
}

bool	can_access_directory(const char	*path)
{
	if (access(path, R_OK | X_OK) == 0)
		return (true);
	else
		return (false);
}

bool	file_or_directory_exists(const char	*path)
{
	struct stat	buffer;

	return (stat(path, &buffer) == 0);
}

int	check_and_export(t_pipex *pipex, char *pwd_to_set, char *pwd, int i)
{
	if (i == 1)
		pwd_to_set = ft_strjoin("PWD", pwd, '=');
	else if (i == 0)
		pwd_to_set = ft_strjoin("OLDPWD", pwd, '=');
	if (!pwd_to_set)
		return (1);
	export_with_option(pipex, pwd_to_set);
	free (pwd_to_set);
	return (0);
}

char	*modify_cmd(char *path, t_pipex *pipex, int i, int j)
{
	char	*home;
	char	*final;

	home = get_var_in_env(pipex->envp, "~", 0);
	final = malloc(ft_strlen(home) + ft_strlen(path));
	if (!final)
		return (NULL);
	i = 0;
	j = 0;
	while (home[i])
	{
		final[j] = home[i];
		i++;
		j++;
	}
	i = 1;
	while (path && path[i])
	{
		final[j] = path[i];
		i++;
		j++;
	}
	final[j] = '\0';
	free(home);
	return (final);
}

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
			printf("minishell: cd: HOME not set\n");
			return (1);
		}
	}
	else if (path && path[0] && path[0] == '-' && ft_strlen(path) == 1)
	{
		modified_cmd = get_var_in_env(pipex->envp, "OLDPWD", 1);
		if (!modified_cmd || modified_cmd == NULL
			|| (modified_cmd && modified_cmd[0] == '\0'))
		{
			printf("minishell: cd: OLDPWD not set\n");
			return (1);
		}
	}
	else if (path && path[0] == '~')
		modified_cmd = modify_cmd(path, pipex, 0, 0);
	else
		modified_cmd = path;
	if (!file_or_directory_exists(modified_cmd))
	{
		printf("minishell: cd: %s: No such file or directory\n", modified_cmd);
		if (path && path[0] == '~')
			free(modified_cmd);
		return (1);
	}
	if (!is_directory(modified_cmd))
	{
		printf("minishell: cd: %s: Not a directory\n", modified_cmd);
		if (path && path[0] == '~')
			free(modified_cmd);
		return (1);
	}
	if (!can_access_directory(modified_cmd))
	{
		printf("minishell: cd: %s: Permission denied\n", modified_cmd);
		if (path && path[0] == '~')
			free(modified_cmd);
		return (1);
	}
	getcwd(old_pwd, PATH_MAX);
	if (chdir(modified_cmd) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", modified_cmd);
		return (1);
	}
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
