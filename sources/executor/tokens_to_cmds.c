/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:35:40 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/14 17:39:15 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include "tokenization.h"
#include "utilities.h"

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
			if (t2->type == WORD)
			{
				cm[*len] = t2->value;
				(*len)++;
			}
			t2 = t2->next;
		}
		cm[*len] = NULL;
	}
}

void	token_to_cmds_helper(t_token *temp2, int *len, t_fds *fds)
{
	if (temp2->type == HERE_DOC)
		fds->infd = here_doc_open(temp2->next->value);
	if (temp2->type == IN_REDIR)
		fds->infd = open_file(temp2->next->value, INPUT);
	if (temp2->type == OUT_REDIR)
		fds->outfd = open_file(temp2->next->value, TRUNC);
	if (temp2->type == APPEND_REDIR)
		fds->outfd = open_file(temp2->next->value, APPEND);
	if (temp2->type == WORD)
		(*len)++;
}

void	init_fds(t_fds *fds)
{
	fds->infd = 0;
	fds->outfd = 1;
	fds->second_case = -1;
}

void	token_to_cmds(t_shell *shell, t_token *tokens)
{
	int		len;
	char	**cmd_args;
	t_token	*temp;
	t_token	*temp2;
	t_fds	fds;

	init_fds(&fds);
	temp = tokens;
	while (temp != NULL)
	{
		len = 0;
		temp2 = temp;
		while (temp2 != NULL && temp2->type != S_PIPE)
		{
			token_to_cmds_helper(temp2, &len, &fds);
			temp2 = temp2->next;
		}
		cmd_args = malloc(sizeof(char *) * (len + 1));
		if (!cmd_args)
			return ;
		token_to_cmds_helper1(&len, temp, cmd_args, NULL);
		ft_lstadd_back(shell, ft_lstnew(cmd_args, &fds));
		token_to_cmds_helper1(&fds.second_case, temp2, NULL, &temp);
	}
	system("leaks minishell");
}
