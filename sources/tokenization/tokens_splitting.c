/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_splitting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:02:29 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/20 19:26:13 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"
#include "utilities.h"
#include <stdlib.h>

extern int	g_exit_status;

void	split_by_spaces(char *cmd_line, t_token **tokens_list)
{
	int		i;
	int		start;

	i = 0;
	start = 0;
	global(0, 1);
	while (cmd_line && cmd_line[i] && cmd_line[i] != '\0')
	{
		if (ft_isspace(cmd_line[i]) == 1)
		{
			if (i >= 1)
				create_and_add_to_list(tokens_list, cmd_line
					+ start, i - start);
			start = i + 1;
		}
		if (cmd_line[i] == '\"' || cmd_line[i] == '\'')
			quote_handling(&i, cmd_line, 1);
		if (cmd_line[i])
			i++;
	}
	if (i - start > 0)
		create_and_add_to_list(tokens_list, cmd_line + start, i - start);
}

void	split_by_operators(t_token **tokens_list)
{
	t_token	*cur_token;
	int		is_op;

	is_op = 0;
	global(0, 1);
	if (!tokens_list)
		return ;
	cur_token = *tokens_list;
	while (cur_token != NULL)
	{
		procces_one_token(cur_token, tokens_list, &is_op, 0);
		cur_token = go_to_next(cur_token, is_op);
	}
}
