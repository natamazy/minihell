/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:46:56 by natamazy          #+#    #+#             */
/*   Updated: 2024/05/11 18:42:58y natamazy         ###   ########.fr       */
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
	new_token->prev = ptr;
}

void	split_by_spaces(char *command_line, t_token **list_of_tokens)
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
		{
			flag = 1;
			j++;
		}
		while (flag == 0 && command_line[j] && ft_isspace(command_line[j]) == 0)
			j++;
		while (flag == 1 && command_line[j] && command_line[j] != '\"')
			j++;
		if (command_line[j] && command_line[j] == '\"')
		{
			flag = 2;
			j++;
		}
		if (flag == 1)
		{
			printf("\nCHES PAKE\n"); // quoty pakac chexnii depqy
			return ;
		}
		new_token = ft_new_token(ft_substr(command_line, i, j - i));
		if (new_token == NULL)
			return ; // knereq der error handling chka mer kodum dra hamar hl@ vor senc
		ft_add_token_to_list(list_of_tokens, new_token);
		i = j;
	}
}

void	split_by_operators(t_token **list_of_tokens)
{
	t_token	*current_token;
	t_token	*new_token;
	t_token	*next_node;
	int		op_len;
	int		i;
	int		non_op_start;
	int		is_op;

	if (!list_of_tokens)
		return ;
	current_token = *list_of_tokens;
	while (current_token != NULL)
	{
		is_op = 0;
		i = 0;
		non_op_start = i;
		while (current_token->value[i])
		{
			char c = current_token->value[i];
			op_len = ft_is_operator(current_token->value, i);
			if (op_len > 0)
			{
				is_op = 1;
				if (i - non_op_start > 0) // in case if there is non operator symbols BEFORE operator
				{
					new_token = ft_new_token(ft_substr(current_token->value, non_op_start, i - non_op_start));
					if (new_token == NULL)
						return ; // knereq der error handling chka mer kodum dra hamar hl@ vor senc
					if (current_token->prev != NULL)
						current_token->prev->next = new_token;
					else
						*list_of_tokens = new_token;
					new_token->next = current_token;
					new_token->prev = current_token->prev;
					current_token->prev = new_token;
				}
				new_token = ft_new_token(ft_substr(current_token->value, i, op_len));
				if (new_token == NULL)
					return ; // knereq der error handling chka mer kodum dra hamar hl@ vor senc
				if (current_token->prev != NULL)
					current_token->prev->next = new_token;
				else
					*list_of_tokens = new_token;
				new_token->next = current_token;
				new_token->prev = current_token->prev;
				current_token->prev = new_token;
				i += op_len;
				non_op_start = i;
			}
			else
				i++;
		}
		if (i - non_op_start > 0 && is_op == 1) // in case if there is non operator symbols AFTER operator
		{
			new_token = ft_new_token(ft_substr(current_token->value, non_op_start, i - non_op_start));
			if (new_token == NULL)
				return ; // knereq der error handling chka mer kodum dra hamar hl@ vor senc
			if (current_token->prev != NULL)
				current_token->prev->next = new_token;
			else
				*list_of_tokens = new_token;
			new_token->next = current_token;
			new_token->prev = current_token->prev;
			current_token->prev = new_token;
		}
		next_node = current_token->next;
		if (is_op != 0)
		{
			if (current_token->prev != NULL)
				current_token->prev->next = current_token->next;
			if (current_token->next)
				current_token->next->prev = current_token->prev;
			free(current_token->value);
			free(current_token);
		}
		current_token = next_node;
	}
}

void	tokenization(char *command_line, t_token **list_of_tokens)
{
	split_by_spaces(command_line, list_of_tokens);
	split_by_operators(list_of_tokens);
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
