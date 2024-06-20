/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:29:46 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/20 13:32:10 by natamazy         ###   ########.fr       */
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
