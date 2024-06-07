/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:06:58 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/06 16:07:13 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utilities.h"

char	*ft_strjoin(char const *s1, char const *s2, char sep)
{
	char	*r_s;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	r_s = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!r_s)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		r_s[j++] = s1[i];
		i++;
	}
	r_s[j++] = sep;
	i = 0;
	while (s2[i])
	{
		r_s[j++] = s2[i];
		i++;
	}
	r_s[j] = '\0';
	return (r_s);
}

int	ft_lstsize(t_env_elem *lst)
{
	int			i;
	t_env_elem	*current;

	i = 0;
	current = lst;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}