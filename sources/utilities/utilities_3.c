/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:07:52 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/06 16:07:09 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utilities.h"

int	ft_env_elem_size(t_env_elem *begin_list)
{
	int	count;

	count = 0;
	while (begin_list)
	{
		count++;
		begin_list = begin_list->next;
	}
	return (count);
}

t_env_elem	*ft_env_elem_at(t_env_elem *begin_list, unsigned int nbr)
{
	unsigned int	i;

	i = 0;
	while (i < nbr && begin_list->next)
	{
		begin_list = begin_list->next;
		i++;
	}
	if (i != nbr)
		return (NULL);
	return (begin_list);
}

t_env_elem	*ft_merge_sorted_list(t_env_elem *left, t_env_elem *right,
			int (*cmp)())
{
	t_env_elem	dummy;
	t_env_elem	*sorted_list;

	sorted_list = &dummy;
	while (left && right)
	{
		if ((*cmp)(left->key, right->key) < 0)
		{
			sorted_list->next = left;
			left = left->next;
		}
		else
		{
			sorted_list->next = right;
			right = right->next;
		}
		sorted_list = sorted_list->next;
	}
	if (left)
		sorted_list->next = left;
	else if (right)
		sorted_list->next = right;
	return (dummy.next);
}

t_env_elem	*merge_sort(t_env_elem *begin_list, int (*cmp)())
{
	t_env_elem	*left;
	t_env_elem	*right;
	t_env_elem	*pre_right;
	int			list_size;

	list_size = ft_env_elem_size(begin_list);
	if (begin_list == NULL || list_size < 2)
		return (begin_list);
	left = begin_list;
	pre_right = ft_env_elem_at(begin_list, (list_size / 2) - 1);
	right = pre_right->next;
	pre_right->next = NULL;
	left = merge_sort(left, cmp);
	right = merge_sort(right, cmp);
	return (ft_merge_sorted_list(left, right, cmp));
}

void	ft_env_elem_sort(t_env_elem **begin_list, int (*cmp)())
{
	*begin_list = merge_sort(*begin_list, cmp);
}
