/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:44:21 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/06 10:22:26 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntaxer.h"
#include "tokenization.h"
#include "utilities.h"

char	*join(char const *s1, char const *s2)
{
	char	*r_s;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	r_s = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!r_s)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		r_s[j++] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		r_s[j++] = s2[i];
		i++;
	}
	r_s[j] = '\0';
	return (r_s);
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
	return (join(join(l_part, var), r_part));
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
			token->value = agvanistan(str, &i, len, envr);
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
