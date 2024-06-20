/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:14:00 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/20 12:46:25 by natamazy         ###   ########.fr       */
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

void	free_2(char *key, char *value)
{
	free(key);
	free(value);
}
