/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:42:48 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/04 23:10:50 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include "tokenization.h"

t_cmd	*ft_lstnew(char **cmd_args)
{
	t_cmd	*new_node;

	new_node = (t_cmd *) malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->cmd_args = cmd_args;
	new_node->cmd_path = cmd_args[0];
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back(t_shell *shell, t_cmd *new)
{
	t_cmd	*current;

	// if (!shell->cmds || !new)
	// 	return ;
	if (shell->cmds == NULL)
	{
		shell->cmds = new;
		return ;
	}
	current = shell->cmds;
	while (current != NULL && current->next != NULL)
		current = current->next;
	current->next = new;
}

void	token_to_cmds(t_shell *shell, t_token *tokens)
{
	int		len;
	char	**cmd_args;
	t_token	*temp;
	t_token	*temp2;

	temp = tokens;
	while (temp)
	{
		len = 0;
		temp2 = temp;
		while (temp2 != NULL && temp2->type != S_PIPE)
		{
			temp2 = temp2->next;
			len++;
		}
		temp2 = temp;
		cmd_args = malloc(sizeof(char *) * (len + 1));
		if (!cmd_args)
			return ;
		len = 0;
		while (temp2 != NULL && temp2->type != S_PIPE)
		{
			cmd_args[len] = temp2->value;
			temp2 = temp2->next;
			len++;
		}
		cmd_args[len] = NULL;
		ft_lstadd_back(shell, ft_lstnew(cmd_args));
		temp = temp2->next;
	}
}
