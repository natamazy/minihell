/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:06:21 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/03 22:17:10 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "utilities.h"
#include "syntaxer.h"
#include "builtin.h"

int	main(int argc, char **argv, char **env)
{
	t_token	*token_list;
	char	*cmd_line;
	t_shell	*shell;

	(void) argv;
	if (argc > 1)
		return (1);
	
	shell = malloc(sizeof(shell));
	shell->envr = init_env(env);
	check_env(shell);

	export_no_option(shell->envr);
	token_list = NULL;
	
	char	**test = env_list_to_array(shell->envr);
	int L = 0;
	while (test[L] != NULL)
	{
		printf("CHAR** - %s\n", test[L]);
		L++;
	}
	
	while (1)
	{
		cmd_line = readline("MINISHELL HOPAR:");
		if (cmd_line && *cmd_line)
		{
			tokenization(cmd_line, &token_list);
			if (syntax_validator(token_list) == 2)
				printf("EROR HAPPENED, not definied yet\n");
			print_token_list(token_list);
			add_history(cmd_line);
		}
		ft_token_list_clear(&token_list);
		free(cmd_line);
	}
	rl_clear_history();
}
