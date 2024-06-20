/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoter_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:00:09 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/20 17:00:33 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntaxer.h"
#include "tokenization.h"
#include "utilities.h"
#include "pipex.h"

void	dollar_opener(t_token *token, int len, t_env_elem *envr)
{
	char	*str;
	int		i;
	int		is_dquote;
	int		is_squote;

	i = 0;
	is_dquote = 0;
	is_squote = 0;
	str = token->value;
	while (str && str[i] != '\0')
	{
		if (is_squote == 0 && str[i] == '\"')
			is_dquote = !is_dquote;
		if (is_dquote == 0 && str[i] == '\'')
			is_squote = !is_squote;
		if (is_squote == 0 && str[i] == '$')
		{
			str = agvanistan(str, &i, len, envr);
			continue ;
		}
		i++;
	}
	token->value = str;
}

void	remove_empty_fields(t_token *token, int empty_fields)
{
	char	*tmp;

	if (empty_fields <= 0)
		return ;
	tmp = ft_strdup(token->value);
	free(token->value);
	token->value = tmp;
}
