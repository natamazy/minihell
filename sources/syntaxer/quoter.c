/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:44:21 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/15 17:35:26 by aggrigor         ###   ########.fr       */
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
	if (var != NULL)
		free(var);
	if (var[0] == '\0')
		return ("$");
	while (envr)
	{
		if (ft_strcmp(var, envr->key) == 0)
		{
			if (envr->value == NULL)
				return ("");
			else
				return (envr->value);
		}
		envr = envr->next;
	}
	return ("");
}

char	*agvanistan(char *str, int *i, int len, t_env_elem *envr)
{
	char	*l_part;
	char	*r_part;
	char	*var;
	int		start;

	l_part = ft_substr(str, 0, *i);
	start = *i;
	while (str[*i] && ft_isspace(str[*i]) == 0 && \
		str[*i] != '"' && str[*i] != '\'')
		(*i)++;
	var = get_var_in_env(envr, ft_substr(str, start + 1, *i - start - 1));
	r_part = ft_substr(str, *i, len - *i);
	*i = start + ft_strlen(var);
	free(str);
	return (join(join(l_part, var), r_part));
}

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
	while (str[i])
	{
		if (is_squote == 0 && str[i] == '\"')
			is_dquote = !is_dquote;
		if (is_dquote == 0 && str[i] == '\'')
			is_squote = !is_squote;
		if (is_squote == 0 && str[i] == '$')
			str = agvanistan(str, &i, len, envr);
		i++;
	}
	token->value = str;
}

void	remove_empty_fields(t_token *token, int empty_fields)
{
	char	*tmp;

	if (empty_fields < 0)
		return ;
	tmp = ft_strdup(token->value);
	free(token->value);
	token->value = tmp;
}
