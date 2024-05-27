/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 19:23:33 by natamazy          #+#    #+#             */
/*   Updated: 2024/05/27 14:26:22 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"
#include "utilities.h"

char	*find_key(char	*full_key_val)
{
	int		i;
	char	*new_key;

	i = 0;
	if (!full_key_val)
		return (NULL);
	while (full_key_val[i] != '=')
		i++;
	if (i == 0)
		return (NULL);
	new_key = malloc((i + 1) * sizeof(char));
	if (!new_key)
		return (NULL);
	i = 0;
	while (full_key_val[i] != '=')
	{
		new_key[i] = full_key_val[i];
		i++;
	}
	new_key[i] = '\0';
	return (new_key);
}

char	*find_value(char	*full_key_val)
{
	int		i;
	int		j;
	char	*new_val;

	i = 0;
	if (!full_key_val)
		return (NULL);
	while (full_key_val[i] != '=')
		i++;
	j = ++i;
	while (full_key_val[j] != '\0')
		j++;
	new_val = malloc((j - i) * sizeof(char));
	if (!new_val)
		return (NULL);
	j = 0;
	while (full_key_val[i] != '\0')
	{
		new_val[j] = full_key_val[i];
		i++;
		j++;
	}
	new_val[j] = '\0';
	return (new_val);
}

t_env_elem	*init_env(char	**env)
{
	int			i;
	t_env_elem	*new_env;
	t_env_elem	temp_env_elem;

	i = 0;
	new_env = &temp_env_elem;
	while (env[i] != NULL)
	{
		new_env->next = malloc(sizeof(t_env_elem));
		if (!new_env->next)
			return (NULL);
		new_env->next->key = find_key(env[i]);
		new_env->next->value = find_value(env[i]);
		new_env->next->next = NULL;
		new_env = new_env->next;
		i++;
	}
	return (temp_env_elem.next);
}
