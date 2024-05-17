/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:43:05 by natamazy          #+#    #+#             */
/*   Updated: 2024/05/17 15:46:49 by natamazy         ###   ########.fr       */
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
	new_token->type = NONE;
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

// line 56
// knereq der error handling chka
// mer kodum dra hamar hl@ vor senc
void	create_and_add_to_list(t_token **token_list, char *start, int len)
{
	t_token	*new_token;

	new_token = ft_new_token(ft_substr(start, 0, len));
	if (new_token == NULL)
		return ;
	ft_add_token_to_list(token_list, new_token);
}

// line 112 / knereq der error handling chka mer kodum dra hamar hl@ vor senc
void	add_new_bef(t_token **tokens_list,
	t_token *cur_token, char *value)
{
	t_token	*new_token;

	new_token = ft_new_token(value);
	if (new_token == NULL)
		return ;
	if (cur_token->prev != NULL)
		cur_token->prev->next = new_token;
	else
		*tokens_list = new_token;
	new_token->next = cur_token;
	new_token->prev = cur_token->prev;
	cur_token->prev = new_token;
}
