/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoter_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:44:21 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/20 17:50:12 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntaxer.h"
#include "tokenization.h"
#include "utilities.h"
#include "pipex.h"

void	remove_extra_helper(t_token *token, int *l, int *r)
{
	token->value[*l] = token->value[*r];
	(*l)++;
	if (token->value[*r])
		(*r)++;
}

int	remove_extra_quotes(t_token *token, int l, int r)
{
	char	quote_type;

	quote_type = 0;
	if (token == NULL || token->value == NULL)
		return (-1);
	while (token->value[r])
	{
		if (token->value[r] == '"' || token->value[r] == '\'')
		{
			if (quote_type == 0)
				quote_type = token->value[r++];
			if (token->value[r] && quote_type == token->value[r])
			{
				r++;
				quote_type = 0;
				continue ;
			}
		}
		remove_extra_helper(token, &l, &r);
	}
	token->value[l] = '\0';
	remove_empty_fields(token, l - r);
	return (0);
}

void	remove_empty_tokens(t_token **tokens, t_token **list)
{
	t_token	*remove;

	remove = *tokens;
	if ((*tokens)->prev)
	{
		(*tokens)->prev->next = (*tokens)->next;
		if ((*tokens)->next)
			(*tokens)->next->prev = (*tokens)->prev;
		(*tokens) = (*tokens)->next;
	}
	else
	{
		*tokens = (*tokens)->next;
		(*list) = *tokens;
		if (*tokens)
			(*tokens)->prev = NULL;
	}
	free(remove->value);
	free(remove);
}

void	expander(t_token *tokens, t_env_elem *envr, t_token **list)
{
	int		old_len;

	while (tokens)
	{
		if (tokens->type == WORD)
		{
			old_len = ft_strlen(tokens->value);
			dollar_opener(tokens, old_len, envr);
			if (tokens && tokens->value && tokens->value[0] == '\0')
			{
				remove_empty_tokens(&tokens, list);
				continue ;
			}
			if (remove_extra_quotes(tokens, 0, 0) == -1)
				p_err(2, "minishell: error while removing extra quotes\n",
					NULL, NULL);
		}
		tokens = tokens->next;
	}
}
