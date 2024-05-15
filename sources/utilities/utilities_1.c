/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:14:48 by aggrigor          #+#    #+#             */
/*   Updated: 2024/05/15 16:21:10 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"
#include "utilities.h"
// TEXAPOXEL HEADER FILE-I MEJ!!!

int	ft_isalpha(int c)
{
	return (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'));
}

int	ft_is_operator(char *s, int i)
{
	int	op_len;

	if (s[i] == '|' || s[i] == '&' || s[i] == '>' || s[i] == '<')
	{
		if (s[i + 1] && s[i] == s[i + 1])
			op_len = 2;
		else
			op_len = 1;
	}
	else
		op_len = 0;
	return (op_len);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

char	*str_type(int token_type)
{
	if (token_type == 0)
		return ("WORD");
	else if (token_type == 1)
		return ("S_PIPE");
	else if (token_type == 2)
		return ("D_PIPE");
	else if (token_type == 3)
		return ("S_AND");
	else if (token_type == 4)
		return ("D_AND");
	else if (token_type == 5)
		return ("O_D_QUOTE");
	else if (token_type == 6)
		return ("C_D_QUOTE");
	else if (token_type == 7)
		return ("O_S_QUOTE");
	else if (token_type == 8)
		return ("C_S_QUOTE");
	else if (token_type == 9)
		return ("IN_REDIR");
	else if (token_type == 10)
		return ("OUT_REDIR");
	else if (token_type == 11)
		return ("HERE_DOC");
	else if (token_type == 12)
		return ("APPEND_REDIR");
	else if (token_type == 13)
		return ("ERROR");
	else if (token_type == 14)
		return ("NONE");
	else
		return ("\033[0;031mTOKEN_TYPE_NOT_FOUND");
}

void	print_token_list(t_token *token_list)
{
	if (!token_list)
		return ;
	while (token_list)
	{
		printf("\033[0;036m%s\033[0;032m(%s)\033[0m",
			str_type(token_list->type), token_list->value);
		if (token_list && token_list->next)
			printf("\033[0;036m -> \033[0m");
		else
			printf("\n");
		token_list = token_list->next;
	}
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (s == NULL)
		return ("");
	if (len <= ft_strlen(s))
		str = (char *) malloc(sizeof(char) * (len + 1));
	else
		str = (char *) malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

void	ft_token_list_clear(t_token **lst)
{
	t_token	*t;
	t_token	*l;

	if (!lst)
		return ;
	l = *lst;
	while (l)
	{
		t = l->next;
		free(l->value);
		free(l);
		l = t;
	}
	*lst = NULL;
}
