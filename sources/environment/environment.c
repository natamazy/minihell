/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 19:23:33 by natamazy          #+#    #+#             */
/*   Updated: 2024/05/26 21:27:27 by natamazy         ###   ########.fr       */
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

void	init_env(char	**env, char	***new_env)
{
	int	env_var_count;

	env_var_count = 0;
	while (env[env_var_count] != NULL)
		env_var_count++;
	new_env = malloc((env_var_count + 1) * sizeof(char **));
	if (!new_env)
		return ;
	env_var_count = 0;
	while (env[env_var_count] != NULL)
	{
		new_env[env_var_count] = malloc(2 * sizeof(char *));
		new_env[env_var_count][KEY] = find_key(env[env_var_count]);
		new_env[env_var_count][VALUE] = find_value(env[env_var_count]);
		printf("OUR | key '%s', value '%s'\n", new_env[env_var_count][KEY], new_env[env_var_count][VALUE]);
		env_var_count++;
	}
	env[env_var_count] = NULL;
}
