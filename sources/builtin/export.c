/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:19:35 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/19 20:45:45 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include "utilities.h"

void	create_copy_helper(t_env_elem **head, t_env_elem **current_new,
							t_env_elem **current_orig, t_env_elem **new_head)
{
	if (*head == NULL)
		return ;
	*new_head = malloc(sizeof(t_env_elem));
	if (*new_head == NULL)
		return ;
	(*new_head)->key = ft_strdup((*head)->key);
	(*new_head)->value = ft_strdup((*head)->value);
	(*new_head)->next = NULL;
	*current_new = *new_head;
	*current_orig = (*head)->next;
}

t_env_elem	*create_copy(t_env_elem *head)
{
	t_env_elem	*current_new;
	t_env_elem	*current_orig;
	t_env_elem	*new_head;

	create_copy_helper(&head, &current_new, &current_orig, &new_head);
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

int	export_no_option(t_env_elem *envr)
{
	t_env_elem	*temp;
	t_env_elem	*ts;

	temp = envr;
	temp = create_copy(envr);
	ft_env_elem_sort(&temp, ft_strcmp);
	ts = temp;
	while (ts)
	{
		if (ts->value && ts->value != NULL && ts->value[0] != '\0' && ft_strlen(ts->key) > 0)
			printf("declare -x %s=\"%s\"\n", ts->key, ts->value);
		else if (ts->key && ts->key != NULL)
			printf("declare -x %s\n", ts->key);
		ts = ts->next;
	}
	free_list(temp);
	temp = NULL;
	return (666);
}

int	print_env(t_env_elem *envr, int *is_builtin)
{
	t_env_elem	*temp;

	temp = envr;
	while (temp)
	{
		if (temp->key && temp->key != NULL && temp->value != NULL && temp->value[0] != '\0' && ft_strlen(temp->key) > 0)
			printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
	*is_builtin = 1;
	return (666);
}

int	export(t_pipex *pipex, t_cmd *cmd, int *is_builtin)
{
	int	exit;

	if (cmd->cmd_args[1] == NULL)
		exit = export_no_option(pipex->envp);
	else
		exit = export_final(pipex, cmd->cmd_args);
	*is_builtin = 1;
	return (exit);
}
