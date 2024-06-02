/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:11:04 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/02 19:07:31 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntaxer.h"
#include "tokenization.h"
#include "utilities.h"

int	syntax_validator(t_token	*token_list)
{
	while (token_list != NULL)
	{
		if (token_list->type == D_PIPE)
			return (2); // syntax error type
		else if (token_list->type == S_PIPE && \
			(token_list->next && ft_is_operator(token_list->value, 0)))
			return (2);
		else if ((token_list->type == OUT_REDIR || token_list->type == IN_REDIR)
			&& token_list->next && (token_list->next->type != FILEIN || token_list->next->type != FILEOUT))
			return (2);
		token_list = token_list->next;
	}
	return (0);
}
