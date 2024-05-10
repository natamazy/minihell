/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:46:56 by natamazy          #+#    #+#             */
/*   Updated: 2024/05/10 17:33:24 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"
#include "utilities.h"
#include <stdlib.h>

t_token	*ft_new_token(char *value, t_token_type type)
{
	t_token *new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->value = value;
	new_token->type = type;
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
	new_token->prev = NULL;
}

void	tokenization(char *command_line, t_token **list_of_tokens)
{
	int	i;
	int	j;
	t_token_type	current_token_type;
	t_token			*new_token;

	i = 0;
	current_token_type = get_token_type(command_line, i);
	while (command_line[i] && ft_isspace(command_line[i]) == 1)
		i++;
	if (command_line[i] == '\0')
		return ;
	j = i;
	while (command_line[j])
	{
		new_token = NULL;

		if (current_token_type != get_token_type(command_line, j))
		{
			new_token = ft_new_token(ft_substr(command_line, i, j), current_token_type);
			if (new_token == NULL)
				return ; // knereq der error handling chka mer kodum dra hamar hl@ vor senc
			ft_add_tokenlist(list_of_tokens, new_token);
			i = j;
			current_token_type = get_token_type(command_line, j);
		}
		else
			j++;
	}
}

t_token_type	get_token_type(char *command_line, int i)
{
	if (!command_line || i < 0)
		return (ERROR);
	if (command_line[i] && command_line[i] == '|')
	{
		if (command_line[i + 1] && command_line[i + 1] == '|')
		{
			i++;
			return (D_PIPE);
		}
		return (S_PIPE);
	}
	if (command_line[i] && command_line[i] == '&')
	{
		if (command_line[i + 1] && command_line[i + 1] == '&')
		{
			i++;
			return (D_AND);
		}
		return (S_AND);
	}
	if (command_line[i] && command_line[i] == '<')
	{
		if (command_line[i + 1] && command_line[i + 1] == '<')
		{
			i++;
			return (L_D_REDIR);
		}
		return (L_S_REDIR);
	}
	if (command_line[i] && command_line[i] == '>')
	{
		if (command_line[i + 1] && command_line[i + 1] == '>')
		{
			i++;
			return (R_D_REDIR);
		}
		return (R_S_REDIR);
	}
	return (ERROR);
}
