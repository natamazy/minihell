/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:08:47 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/17 20:23:42 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "builtin.h"
#include "minishell.h"
#include "utilities.h"

void	cd(char *path, t_pipex *pipex, int *is_builtin)
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];
	char	*pwd_to_set;

	getcwd(old_pwd, PATH_MAX);
	if (chdir(path) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", path);
		exit(1);
	}
	pwd_to_set = ft_strjoin("OLDPWD", old_pwd, '=');
	if (!pwd_to_set)
		return ;
	export_with_option(pipex, pwd_to_set);
	getcwd(new_pwd, PATH_MAX);
	free(pwd_to_set);
	pwd_to_set = ft_strjoin("PWD", new_pwd, '=');
	if (!pwd_to_set)
		return ;
	free(pwd_to_set);
	export_with_option(pipex, pwd_to_set);
	*is_builtin = 1;
}
