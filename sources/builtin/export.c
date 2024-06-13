/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:19:35 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/13 16:58:21 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include "utilities.h"

t_env_elem	*create_copy(t_env_elem *head)
{
	t_env_elem	*current_new;
	t_env_elem	*current_orig;
	t_env_elem	*new_head;

	if (head == NULL)
		return (NULL);
	new_head = malloc(sizeof(t_env_elem));
	if (new_head == NULL)
		return (NULL);
	new_head->key = ft_strdup(head->key);
	new_head->value = ft_strdup(head->value);
	new_head->next = NULL;
	current_new = new_head;
	current_orig = head->next;
	while (current_orig != NULL)
	{
		current_new->next = malloc(sizeof(t_env_elem));
		if (current_new->next == NULL)
			return (NULL);
		current_new = current_new->next;
		current_new->key = ft_strdup(current_orig->key);
		current_new->value = ft_strdup(current_orig->value);
		current_new->next = NULL;
		current_orig = current_orig->next;
	}
	return (new_head);
}

void	free_list(t_env_elem *head)
{
	t_env_elem	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void	export_no_option(t_env_elem *envr)
{
	t_env_elem	*temp;
	t_env_elem	*ts;

	temp = envr;
	temp = create_copy(envr);
	ft_env_elem_sort(&temp, ft_strcmp);
	ts = temp;
	while (ts)
	{
		if (ts->value[0] != '\0' && ft_strlen(ts->key) > 0)
			printf("declare -x %s=\"%s\"\n", ts->key, ts->value);
		else
			printf("declare -x %s\n", ts->key);
		ts = ts->next;
	}
	free_list(temp);
	temp = NULL;
}

void	print_env(t_env_elem *envr)
{
	t_env_elem	*temp;

	temp = envr;
	while (temp)
	{
		if (temp->value[0] != '\0' && ft_strlen(temp->key) > 0)
			printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}

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

void	export(t_shell *shell, char *var)
{
	t_env_elem	*temp;
	char		*key;
	char		*value;

	if (is_there_eq_sign(var) == 1)
	{
		key = find_key(var);
		value = find_value(var);
	}
	else
	{
		key = ft_strdup(var);
		value = NULL;
	}
	temp = shell->envr;
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
			temp->next = malloc(sizeof(t_env_elem));
			if (!temp->next)
				return ;
			temp = temp->next;
			temp->key = ft_strdup(key);
			if (value != NULL)
				temp->value = ft_strdup(value);
			else
				temp->value = "\0";
			temp->next = NULL;
			temp = temp->next;
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
