/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:46:56 by natamazy          #+#    #+#             */
/*   Updated: 2024/05/09 16:09:07 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

void	tokenization(char *command_line, t_token *list_of_tokens)
{
	int	i;
	int	j;
	t_token_type	current_token_type;

	i = 0;
	j = i;
	current_token_type = get_token_type(command_line[i]);
	while (command_line[i])
	{
		while (is_space(command_line[i]))
			i++;
		if (current_token_type != get_token_type(command_line[j]))
		{
			// add to list
			i = j;
			current_token_type = get_token_type(command_line[i]);
		}
		else
			j++;
	}
}
