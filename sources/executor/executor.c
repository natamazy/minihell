/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:42:48 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/06 17:33:59 by natamazy         ###   ########.fr       */
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

void	token_to_cmds_helper1(int *len, t_token *t2, char **cm, t_token **t)
{
	if (*len == -1)
	{
		if (t2 != NULL)
			*t = t2->next;
		else
			*t = t2;
	}
	else
	{
		*len = 0;
		while (t2 != NULL && t2->type != S_PIPE)
		{
			cm[*len] = t2->value;
			t2 = t2->next;
			(*len)++;
		}
		cm[*len] = NULL;
	}
}

void	token_to_cmds(t_shell *shell, t_token *tokens)
{
	int		len;
	char	**cmd_args;
	t_token	*temp;
	t_token	*temp2;
	int		second_case;

	second_case = -1;
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
		token_to_cmds_helper1(&len, temp2, cmd_args, NULL);
		ft_lstadd_back(shell, ft_lstnew(cmd_args));
		token_to_cmds_helper1(&second_case, temp2, NULL, &temp);
	}
}
