/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:19:35 by natamazy          #+#    #+#             */
/*   Updated: 2024/05/28 10:35:48 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include "utilities.h"

void	export_no_option(t_env_elem *envr)
{
	t_env_elem	*temp;

	temp = envr;
	while (temp)
	{
		printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
		temp = temp->next;
	}
}

// void	export(t_shell *shell, char *var)
// {
// 	t_env_elem	*temp;
// 	char		*key;
// 	char		*value;

// 	key = find_key(var);
// 	value = find_value(var);
// 	printf("'%s' '%s'\n", key, value);
// }
