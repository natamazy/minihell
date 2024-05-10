/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:14:48 by aggrigor          #+#    #+#             */
/*   Updated: 2024/05/10 22:40:08 by natamazy         ###   ########.fr       */
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