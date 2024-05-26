/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type_defining.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:45:28 by natamazy          #+#    #+#             */
/*   Updated: 2024/05/26 19:16:38 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"
#include "utilities.h"
#include <stdlib.h>

void	set_tokens(t_token *tokens_list)
{
	t_token			*cur_token;

	cur_token = tokens_list;
	while (cur_token != NULL)
	{
		cur_token->type = get_token_type(cur_token->value, 0);
		if (cur_token->prev != NULL && cur_token->type == WORD
			&& ft_is_operator(cur_token->prev->value, 0) > 0)
		{
			if (cur_token->prev->type == IN_REDIR)
				cur_token->type = FILEIN;
			if (cur_token->prev->type == HERE_DOC)
				cur_token->type = LIMITER;
			if (cur_token->prev->type == OUT_REDIR)
				cur_token->type = FILEOUT;
			if (cur_token->prev->type == APPEND_REDIR)
				cur_token->type = APPEND_FILEOUT;
		}
		cur_token = cur_token->next;
	}
}

t_token_type	get_token_type_util(char *s, int i)
{
	if (s[i] == '|')
	{
		if (s[i + 1] && s[i] == s[i + 1])
			return (D_PIPE);
		return (S_PIPE);
	}
	else if (s[i] == '&')
	{
		if (s[i + 1] && s[i] == s[i + 1])
			return (D_AND);
		return (ERROR);
	}
	else if (s[i] == '>')
	{
		if (s[i + 1] && s[i] == s[i + 1])
			return (APPEND_REDIR);
		return (OUT_REDIR);
	}
	else if (s[i] == '<')
	{
		if (s[i + 1] && s[i] == s[i + 1])
			return (HERE_DOC);
		return (IN_REDIR);
	}
	return (WORD);
}

t_token_type	get_token_type(char *s, int i)
{
	if (!s || i < 0)
		return (ERROR);
	return (get_token_type_util(s, i));
}
