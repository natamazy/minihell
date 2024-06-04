/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:06:21 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/04 17:00:14 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "utilities.h"
#include "syntaxer.h"
#include "builtin.h"
#include "executor.h"

int	main(int argc, char **argv, char **env)
{
	t_token	*token_list;
	char	*cmd_line;
	t_shell	*shell;

	(void) argv;
	if (argc > 1)
		return (1);
	
	shell = malloc(sizeof(t_shell));
	shell->envr = init_env(env);
	shell->cmds = NULL;
	check_env(shell);

	export_no_option(shell->envr);
	token_list = NULL;
	
	char	*test[] = {"PATH=/usr/bin:/bin:/usr/sbin:/sbin", "x=12", NULL};
	
	while (1)
	{
		cmd_line = readline("MINISHELL HOPAR:");
		if (cmd_line && *cmd_line)
		{
			tokenization(cmd_line, &token_list);
			if (syntax_validator(token_list) == 2)
				printf("EROR HAPPENED, not definied yet\n");
			token_to_cmds(shell, token_list);
			execve(shell->cmds->cmd_path, shell->cmds->cmd_args, test);
			print_token_list(token_list);
			add_history(cmd_line);
		}
		ft_token_list_clear(&token_list);
		free(cmd_line);
	}
	rl_clear_history();
}
