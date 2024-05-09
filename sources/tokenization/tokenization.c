/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:46:56 by natamazy          #+#    #+#             */
/*   Updated: 2024/05/09 21:50:07 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenization.h"
#include "../../includes/utils.h"
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

void	ft_add_tokenlist(t_token **list_of_tokens, t_token *new_token)
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
	j = i;
	while (command_line[j]) // NAREK(TAMAZYAN) ES 20 ROPE TANJVEL EM NRA HAMAR VOR command_line[i]-i 'i'-n 'j' chsarqecir AaAAAAAAAAaaAAAAAAAAAAAA
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
		return (777); // in case if invalid arguments was passed
	if (command_line[i] && ft_isalpha(command_line[i]))
		return (WORD);
	if (command_line[i] && command_line[i] == '<')
		return (L_ARR);
	if (command_line[i] && command_line[i] == '>')
		return (R_ARR);
	return (-1);
}
