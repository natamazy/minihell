/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:59:58 by natamazy          #+#    #+#             */
/*   Updated: 2024/05/17 16:58:41 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"
#include "utilities.h"

void	print_token_list(t_token *token_list)
{
	if (!token_list)
		return ;
	while (token_list)
	{
		printf("\033[0;035m%s\033[0;032m(%s)\033[0m",
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
