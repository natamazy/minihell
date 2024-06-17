/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:14:00 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/17 20:00:35 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "builtin.h"
#include "minishell.h"
#include "utilities.h"

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

void	export_helper_1(char **key, char **value, char *var)
{
	if (is_there_eq_sign(var) == 1)
	{
		*key = find_key(var);
		*value = find_value(var);
	}
	else
	{
		*key = ft_strdup(var);
		*value = NULL;
	}
}

void	export_helper_2(t_env_elem **temp, char *key, char *value)
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

void	export_with_option(t_pipex *pipex, char *var)
{
	t_env_elem	*temp;
	char		*key;
	char		*value;

	export_helper_1(&key, &value, var);
	temp = pipex->envp;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			free(temp->value);
			if (value == NULL || value[0] == '\0')
				temp->value = NULL;
			else
				temp->value = ft_strdup(value);
			return ;
		}
		else if (temp->next == NULL)
		{
			export_helper_2(&temp, key, value);
			break ;
		}
		temp = temp->next;
	}
}

void	unset(t_shell *shell, char *key_to_unset)
{
	t_env_elem	*temp;

	temp = shell->envr;
	while (temp)
	{
		if (ft_strcmp(temp->key, key_to_unset) == 0)
		{
			free(temp->key);
			if (temp->value[0] != '\0')
				free(temp->value);
			return ;
		}
		temp = temp->next;
	}
}
