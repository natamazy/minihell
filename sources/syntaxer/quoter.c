/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:44:21 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/05 21:36:52 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntaxer.h"
#include "tokenization.h"
#include "utilities.h"

char	*str_joiner(char const *s1, char const *s2, char const *s3)
{
	char	*str1;

	printf("-----------%s-%s-%s------------\n", s1, s2, s3);
	str1 = ft_strjoin(s1, s2, "");
	return (ft_strjoin(str1, s3, ""));
}

char	*get_var_in_env(t_env_elem *envr, char *var)
{
	while (envr)
	{
		if (ft_strcmp(var, envr->key) == 0)
		{
			if (envr->value == NULL)
			{
				free(var);
				return ("");
			}
			else
			{
				free(var);
				return (envr->value);
			}
		}
		envr = envr->next;
	}
	free(var);
	return ("");
}	

char	*agvanistan(char *str, int *i, int len, t_env_elem *envr)
{
	char	*l_part = ft_substr(str, 0, *i);
	int		start;
	
	start = *i;
	while (str[*i] && ft_isspace(str[*i]) == 0)
		(*i)++;
	char *var = get_var_in_env(envr, ft_substr(str, start + 1, *i - start - 1));
	char *r_part = ft_substr(str, *i, len - *i);
	free(str);
	return (str_joiner(l_part, var, r_part));
}

void	dollar_opener(t_token *token, int len, t_env_elem *envr)
{
	char	*str = token->value;
	int i = 0;
	int is_dquote = 0;
	int is_squote = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			is_dquote = !is_dquote;
		if (is_dquote == 0 && str[i] == '\'')
			is_squote = !is_squote;
		if (is_squote == 0 && str[i] == '$')
			str = agvanistan(str, &i, len, envr);
		i++;
	}
}

void	expander(t_token *tokens, t_env_elem *envr)
{
	while (tokens)
	{
		if (tokens->type == WORD)
			dollar_opener(tokens, ft_strlen(tokens->value), envr);
		tokens = tokens->next;
	}
}
