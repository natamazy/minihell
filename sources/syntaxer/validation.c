/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:11:04 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/20 06:03:43 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntaxer.h"
#include "pipex.h"
#include "tokenization.h"
#include "utilities.h"

int	is_ctrl_op(t_token	*token)
{
	if (!token->value)
		return (1);
	if (token->type == S_PIPE || token->type == D_PIPE \
		|| token->type == S_AND || token->type == D_AND)
		return (1);
	return (0);
}

int	is_permited(t_token	*token)
{
	if (token->type == D_PIPE || token->type == S_AND || token->type == D_AND)
		return (1);
	return (0);
}

int	syntax_validator(t_token	*t_l)
{
	while (t_l != NULL)
	{
		if (t_l->type == OUT_REDIR || t_l->type == IN_REDIR \
			|| t_l->type == APPEND_REDIR || t_l->type == HERE_DOC)
		{
			if (t_l->next == NULL)
			{
				perror_exit(SYNTAX_ERR, NULL, t_l->value, 2);
				return (2);
			}
			if (t_l->next->type == FILEOUT || t_l->next->type == FILEIN \
				|| t_l->next->type == APPEND_FILEOUT \
				|| t_l->next->type == LIMITER)
				return (0);
			perror_exit(SYNTAX_ERR, NULL, t_l->value, 2);
			return (2);
		}
		if (t_l->type == S_PIPE && !t_l->prev)
		{
			perror_exit(SYNTAX_ERR, NULL, t_l->value, 2);
			return (2);
		}
		if (t_l->type == S_PIPE && !t_l->next)
		{
			perror_exit(SYNTAX_ERR, NULL, t_l->value, 2);
			return (2);
		}
		if (t_l->type == S_PIPE && is_ctrl_op(t_l->next))
		{
			perror_exit(SYNTAX_ERR, NULL, t_l->value, 2);
			return (2);
		}
		if (is_permited(t_l))
		{
			perror_exit(SYNTAX_ERR, NULL, t_l->value, 2);
			return (2);
		}
		t_l = t_l->next;
	}
	return (0);
}
