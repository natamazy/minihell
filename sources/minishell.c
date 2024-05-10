/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:06:21 by natamazy          #+#    #+#             */
/*   Updated: 2024/05/10 12:01:53 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/tokenization.h"
#include "../includes/utils.h"
#include "../readline/include/readline/readline.h"
#include "../readline/include/readline/history.h"

int	main(void)
{
	t_token	*token_list;
	char	*cmd_line;

	token_list = NULL;
	while (1)
	{
		cmd_line = readline("MINISHELL HOPAR:");
		if (cmd_line && *cmd_line)
		{
			tokenization(cmd_line, &token_list);
			print_token_list(token_list);
			add_history(cmd_line);
		}
			
	}
}
