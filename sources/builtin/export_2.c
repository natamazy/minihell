/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:14:00 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/20 00:25:37 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "builtin.h"
#include "minishell.h"
#include "utilities.h"

int	is_valid_ident(char *str);

int	is_there_eq_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	export_helper_1(char **key, char **value, char *var)
{
	if (is_there_eq_sign(var) == 1)
	{
		*key = find_key(var);
		*value = find_value(var);
	}
	else
	{
		*key = ft_strdup(var);
		*value = ft_strdup("\0");
	}
	if (*key && *key != NULL && is_valid_ident(*key) == FALSE)
	{
		printf("bash: export: `%s': not a valid identifier\n", *key);
		free (*key);
		if (*value && *value != NULL)
			free (*value);
		return (FALSE);
	}
	return (TRUE);
}

void	export_helper_2(t_env_elem **temp, char *key, char *value, int flag)
{
	if (flag == 1)
	{
		(*temp)->next = malloc(sizeof(t_env_elem));
		if (!(*temp)->next)
			return ;
		(*temp) = (*temp)->next;
		(*temp)->key = ft_strdup(key);
		if (value != NULL)
			(*temp)->value = ft_strdup(value);
		else
			(*temp)->value = "\0";
		(*temp)->next = NULL;
		(*temp) = (*temp)->next;
	}
	free(value);
	free(key);
}

void	put_value(t_env_elem **temp, char **key, char **value)
{
	free((*temp)->value);
	if (*value == NULL || *value[0] == '\0')
		(*temp)->value = NULL;
	else
		(*temp)->value = ft_strdup(*value);
	export_helper_2(NULL, *key, *value, 0);
}

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
			{
				free(key);
				free(value);
			}
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
	while (var[i] != NULL)
	{
		if (var && var[i] && var[i][0] && var[i][0] == '=')
		{
			printf("bash: unset: `%s': not a valid identifier\n", var[i]);
			err = 1;
			i++;
			continue ;
		}
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

int	ft_isalpha_ident(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (TRUE);
	return (FALSE);
}

int	ft_isdigit(int c)
{
	if (c > '0' && c < '9')
		return (TRUE);
	return (FALSE);
}

int	ft_isalphadigit(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_' || (c > '0' && c < '9'))
		return (TRUE);
	return (FALSE);
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
			printf("bash: unset: `%s': not a valid identifier\n", cmd->cmd_args[i]);
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
