/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:46:56 by natamazy          #+#    #+#             */
/*   Updated: 2024/05/12 20:50:17 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"
#include "utilities.h"
#include <stdlib.h>

t_token	*ft_new_token(char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->value = value;
	new_token->type = ERROR;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

void	ft_add_token_to_list(t_token **list_of_tokens, t_token *new_token)
{
	t_token	*ptr;

	if (list_of_tokens == NULL || new_token == NULL)
		return ;
	if (*list_of_tokens == NULL)
	{
		*list_of_tokens = new_token;
		return ;
	}
	ptr = *list_of_tokens;
	while (ptr && ptr->next)
		ptr = ptr->next;
	ptr->next = new_token;
	new_token->prev = ptr;
}

void	create_and_add_to_list(t_token **token_list, char *start, int len)
{
	t_token	*new_token;

	new_token = ft_new_token(ft_substr(start, 0, len));
	if (new_token == NULL)
		return ; // knereq der error handling chka
				//mer kodum dra hamar hl@ vor senc
	ft_add_token_to_list(token_list, new_token);
}

void	split_by_spaces(char *cmd_line, t_token **token_list)
{
	int		i;
	int		start;
	int		quote;

	i = -1;
	quote = CLOSED;
	start = 0;
	while (cmd_line[++i])
	{
		if (ft_isspace(cmd_line[i]) == 1)
		{
			if (quote == CLOSED && i >= 1 && ft_isspace(cmd_line[i - 1]) == 0)
				create_and_add_to_list(token_list, cmd_line + start, i - start);
			if (quote == CLOSED)
				start = i + 1;
		}
		if (cmd_line[i] == '\"' || cmd_line[i] == '\'')
			quote = !quote;
	}
	if (i - start > 0)
		create_and_add_to_list(token_list, cmd_line + start, i - start);
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

void	add_new_token_before(t_token **tokens_list, t_token *cur_token, char *value)
{
	t_token	*new_token;

	new_token = ft_new_token(value);
	if (new_token == NULL)
		return ; // knereq der error handling chka mer kodum dra hamar hl@ vor senc
	if (cur_token->prev != NULL)
		cur_token->prev->next = new_token;
	else
		*tokens_list = new_token;
	new_token->next = cur_token;
	new_token->prev = cur_token->prev;
	cur_token->prev = new_token;
}

void	split_by_operators(t_token **tokens_list)
{
	t_token	*cur_token;
	int		op_len;
	int		i;
	int		non_op_start;
	int		is_op;

	if (!tokens_list)
		return ;
	cur_token = *tokens_list;
	while (cur_token != NULL)
	{
		is_op = 0;
		i = 0;
		non_op_start = i;
		while (cur_token->value[i])
		{
			op_len = ft_is_operator(cur_token->value, i);
			if (op_len > 0)
			{
				is_op = 1;
				if (i - non_op_start > 0) // in case if there is non operator symbols BEFORE operator
					add_new_token_before(tokens_list, cur_token, ft_substr(cur_token->value, non_op_start, i - non_op_start));
				add_new_token_before(tokens_list, cur_token, ft_substr(cur_token->value, i, op_len));
				i += op_len;
				non_op_start = i;
			}
			else
				i++;
		}
		if (i - non_op_start > 0 && is_op == 1) // in case if there is non operator symbols AFTER operator
			add_new_token_before(tokens_list, cur_token, ft_substr(cur_token->value, non_op_start, i - non_op_start));
		cur_token = go_to_next(cur_token, is_op);
	}
}

void	tokenization(char *command_line, t_token **token_list)
{
	split_by_spaces(command_line, token_list);
	//TODO: add one new spliting level by quotation marks
	// print_token_list(*token_list);
	split_by_operators(token_list);
}

// t_token_type	get_token_type(char *command_line, int i)
// {
// 	if (!command_line || i < 0)
// 		return (ERROR);
// 	if (command_line[i] && command_line[i] == '|')
// 	{
// 		if (command_line[i + 1] && command_line[i + 1] == '|')
// 		{
// 			i++;
// 			return (D_PIPE);
// 		}
// 		return (S_PIPE);
// 	}
// 	if (command_line[i] && command_line[i] == '&')
// 	{
// 		if (command_line[i + 1] && command_line[i + 1] == '&')
// 		{
// 			i++;
// 			return (D_AND);
// 		}
// 		return (S_AND);
// 	}
// 	if (command_line[i] && command_line[i] == '<')
// 	{
// 		if (command_line[i + 1] && command_line[i + 1] == '<')
// 		{
// 			i++;
// 			return (L_D_REDIR);
// 		}
// 		return (L_S_REDIR);
// 	}
// 	if (command_line[i] && command_line[i] == '>')
// 	{
// 		if (command_line[i + 1] && command_line[i + 1] == '>')
// 		{
// 			i++;
// 			return (R_D_REDIR);
// 		}
// 		return (R_S_REDIR);
// 	}
// 	return (ERROR);
// }
