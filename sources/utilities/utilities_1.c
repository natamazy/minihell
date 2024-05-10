/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:14:48 by aggrigor          #+#    #+#             */
/*   Updated: 2024/05/10 12:40:08 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"
#include "utilities.h"
 // TEXAPOXEL HEADER FILE-I MEJ!!!

int	ft_isalpha(int c)
{
	return (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'));
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

void	print_token_list(t_token *token_list)
{
	if (!token_list)
		return ;
	while (token_list)
	{
		printf("type: %d | [%s]", token_list->type, token_list->value);
		if (token_list && token_list->next)
			printf(" -> ");
		else
			printf("\n");
		token_list = token_list->next;
	}
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	s_len;
	unsigned int	substr_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len < start)
		substr_len = 0;
	else if (s_len < len)
		substr_len = s_len;
	else
		substr_len = len;
	substr = (char *)malloc(substr_len + 1);
	if (substr == NULL)
		return (NULL);
	s += start;
	substr[substr_len] = '\0';
	while (substr_len--)
		substr[substr_len] = s[substr_len];
	return (substr);
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