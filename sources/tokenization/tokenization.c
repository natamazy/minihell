/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:46:56 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/20 17:24:23 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"
#include "utilities.h"
#include "pipex.h"
#include <stdlib.h>

extern int	g_exit_status;

void	quote_handling(int *i, char *cmd_line, int print)
{
	int		j;

	j = *i;
	*i = *i + 1;
	while (cmd_line[*i] && (cmd_line[j] != cmd_line[*i]))
		*i = *i + 1;
	if (cmd_line[*i] == '\0' && print)
		perror_exit(QUOT_ERR, NULL, &cmd_line[j], 2);
	else
		global(0, 1);
}

t_token	*go_to_next(t_token *current_token, int need_to_del)
{
	t_token	*next_node;

	next_node = current_token->next;
	if (need_to_del == 1)
	{
		if (current_token->prev != NULL)
			current_token->prev->next = current_token->next;
		if (current_token->next)
			current_token->next->prev = current_token->prev;
		free(current_token->value);
		free(current_token);
	}
	return (next_node);
}

void	procces_one_token(t_token *cur, t_token **tl, int *is_op, int i)
{
	int	op_len;
	int	tok_s;

	tok_s = i;
	while (cur->value[i])
	{
		if (cur->value[i] == '\"' || cur->value[i] == '\'')
			quote_handling(&i, cur->value, 1);
		op_len = ft_is_operator(cur->value, i);
		if (op_len > 0)
		{
			*is_op = 1;
			if (i - tok_s > 0)
				add_new_bef(tl, cur, ft_substr(cur->value, tok_s, i - tok_s));
			add_new_bef(tl, cur, ft_substr(cur->value, i, op_len));
			i += op_len;
			tok_s = i;
			if (i - tok_s > 0 && *is_op == 1)
				add_new_bef(tl, cur, ft_substr(cur->value, tok_s, i - tok_s));
		}
		else
			i++;
	}
	if (i - tok_s > 0 && *is_op == 1)
		add_new_bef(tl, cur, ft_substr(cur->value, tok_s, i - tok_s));
}

//TODO: add one new spliting level by quotation marks
// print_token_list(*token_list);
void	tokenization(char *command_line, t_token **tokens_list)
{
	split_by_spaces(command_line, tokens_list);
	if (global(0, 0) != 0)
		return ;
	split_by_operators(tokens_list);
	if (global(0, 0) != 0)
		return ;
	set_tokens(*tokens_list);
}
