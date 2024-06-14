/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoter_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:44:21 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/14 17:25:30 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntaxer.h"
#include "tokenization.h"
#include "utilities.h"

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
			if (quote_type == token->value[r])
			{
				r++;
				quote_type = 0;
				continue ;
			}
		}
		token->value[l] = token->value[r];
		l++;
		r++;
	}
	token->value[l] = '\0';
	remove_empty_fields(token, l - r);
	return (0);
}

void	expander(t_token *tokens, t_env_elem *envr)
{
	while (tokens)
	{
		if (tokens->type == WORD)
		{
			dollar_opener(tokens, ft_strlen(tokens->value), envr);
			if (remove_extra_quotes(tokens, 0, 0) == -1)
				printf("HAAY HAAAAY OP STOP BABY ERROR@ STEX DU UR ES GNUM\n");
		}
		tokens = tokens->next;
	}
}
