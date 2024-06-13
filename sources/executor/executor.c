/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:42:48 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/13 16:39:18 by natamazy         ###   ########.fr       */
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
	new_node->infile = 0;
	new_node->outfile = 1;
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

int	open_file(char *file_name, int type)
{
	int	fd;

	fd = -1;
	if (type == INPUT)
	{
		fd = open(file_name, O_RDONLY);
		if (fd < 0)
			fd = -2;
	}
	else if (type == TRUNC)
		fd = open(file_name, O_CREAT, 0644);
	else if (type == APPEND)
		fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd > 2)
		return (fd);
	if (fd == -1)
	{
		printf("minihell: %s: Permission denied\n", file_name);
		exit(1);
	}
	if (fd == -2)
	{
		printf("minihell: %s: No such file or directory\n", file_name);
		exit(1);
	}
	return (-1);
}

void	token_to_cmds_helper(t_token *temp2, int *len, t_fds *fds)
{
	// here doc openy pti ashxatcne heredocy trmp fayl bace mejy gre fdn veradardzne
	// args (char *lim);
	// if (temp2->type == HERE_DOC)
	// 	fds.infd = here_doc_open(temp2->next->value);
	if (temp2->type == IN_REDIR)
		fds->infd = open_file(temp2->next->value, INPUT);
	if (temp2->type == OUT_REDIR)
		fds->outfd = open_file(temp2->next->value, TRUNC);
	if (temp2->type == APPEND_REDIR)
		fds->outfd = open_file(temp2->next->value, APPEND);
	if (temp2->type == WORD)
		(*len)++;
}

void	token_to_cmds(t_shell *shell, t_token *tokens)
{
	int		len;
	char	**cmd_args;
	t_token	*temp;
	t_token	*temp2;
	t_fds	fds;

	fds.second_case = -1;
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
		ft_lstadd_back(shell, ft_lstnew(cmd_args));
		token_to_cmds_helper1(&fds.second_case, temp2, NULL, &temp);
	}
}
