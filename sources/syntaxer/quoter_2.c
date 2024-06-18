/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoter_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarapet <nkarapet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:44:21 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/18 16:38:15 by nkarapet         ###   ########.fr       */
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
	int	old_len;

	while (tokens)
	{
		if (tokens->type == WORD)
		{
			old_len = ft_strlen(tokens->value);
			dollar_opener(tokens, old_len, envr);
			// if (old_len > 0 && ft_strlen(tokens->value) == 0)
			if (remove_extra_quotes(tokens, 0, 0) == -1)
				printf("HAAY HAAAAY OP STOP BABY ERROR@ STEX DU UR ES GNUM\n");
		}
		tokens = tokens->next;
	}
}
