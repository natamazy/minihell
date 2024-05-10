/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:46:56 by natamazy          #+#    #+#             */
/*   Updated: 2024/05/10 22:51:16 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"
#include "utilities.h"
#include <stdlib.h>

t_token	*ft_new_token(char *value)
{
	t_token *new_token;

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
	new_token->prev = NULL;
}
void	split_at_tokens(char *command_line, t_token **list_of_tokens)
{
	int	i;
	int	j;
	int	flag;
	t_token	*new_token;

	i = 0;
	j = 0;
	while (command_line[j])
	{
		flag = 0;
		while (command_line[j] && ft_isspace(command_line[j]) == 1)
			j++;
		i = j;
		if (command_line[j] && command_line[j] == '\"')
			flag = 1;
		printf("\n===\n");
		while (flag == 0 && command_line[j] && ft_isspace(command_line[j]) == 0)
		{
			printf("%c", command_line[j]);
			j++;
		}
		printf("\n");
		while (flag == 1 && command_line[j] && command_line[j] != '\"')
			j++;
		if (command_line[j] && command_line[j] == '\"')
			flag = 2;
		if (flag == 1)
		{
			printf("\nCHES PAKE\n");
			return ;
		}
		new_token = ft_new_token(ft_substr(command_line, i, j));
		if (new_token == NULL)
			return ; // knereq der error handling chka mer kodum dra hamar hl@ vor senc
		ft_add_token_to_list(list_of_tokens, new_token);
		i = j;
	}
}

void	tokenization(char *command_line, t_token **list_of_tokens)
{
	split_at_tokens(command_line, list_of_tokens);
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
