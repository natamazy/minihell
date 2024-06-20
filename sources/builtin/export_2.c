/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:14:00 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/20 18:57:48 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "builtin.h"
#include "minishell.h"
#include "utilities.h"

int	export_with_option(t_pipex *pipex, char *var)
{
	t_env_elem	*temp;
	char		*key;
	char		*value;

	if (export_helper_1(&key, &value, var) == FALSE)
		return (1);
	temp = pipex->envp;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			if (value == NULL || value[0] == '\0')
				free_2(key, value);
			else
				put_value(&temp, &key, &value);
			return (0);
		}
		else if (temp->next == NULL)
		{
			export_helper_2(&temp, key, value, 1);
			break ;
		}
		temp = temp->next;
	}
	return (0);
}

int	export_final(t_pipex *pipex, char **var)
{
	int	i;
	int	err;

	i = 1;
	err = 0;
	while (var[i] != NULL)
	{
		if (var && var[i] && var[i][0] && var[i][0] == '=')
		{
			p_err(1, "minishell: export: `", var[i],
				"': not a valid identifier\n");
			err = 1;
			i++;
			continue ;
		}
		if (err == 1)
			export_with_option(pipex, var[i]);
		else
			err = export_with_option(pipex, var[i]);
		i++;
	}
	return (err);
}

void	unset_helper(t_pipex *pipex, char *key_to_unset)
{
	t_env_elem	*temp;

	temp = pipex->envp;
	while (temp)
	{
		if (ft_strcmp(temp->key, key_to_unset) == 0)
		{
			free(temp->key);
			temp->key = NULL;
			if (temp->value && temp->value[0] != '\0')
			{
				free(temp->value);
				temp->value = NULL;
			}
		}
		temp = temp->next;
	}
}

int	is_valid_ident(char *str)
{
	int	i;

	i = 0;
	if (str && str[0] && ft_isalpha_ident(str[0]) == FALSE)
		return (FALSE);
	i++;
	while (str && str[i])
	{
		if (ft_isalphadigit(str[i]) == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	unset(t_pipex *pipex, t_cmd *cmd, int *is_builtin)
{
	int	i;
	int	err;

	i = 1;
	err = 0;
	*is_builtin = 1;
	while (cmd && cmd->cmd_args && cmd->cmd_args[i])
	{
		if (is_valid_ident(cmd->cmd_args[i]) == FALSE)
		{
			p_err(1, "bash: unset: `", cmd->cmd_args[i],
				"': not a valid identifier\n");
			err = 1;
			i++;
			continue ;
		}
		else
			unset_helper(pipex, cmd->cmd_args[i]);
		i++;
	}
	return (err);
}
