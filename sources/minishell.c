/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:06:21 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/14 18:32:05 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "utilities.h"
#include "syntaxer.h"
#include "builtin.h"
#include "executor.h"

char	*read_all(int fd)
{
	if (fd == -1)
		return ("-1");
	else if (fd == 0)
		return ("NULL");
	char *buff = malloc(1000001);
	if (buff == NULL)
		return (NULL);
	int readed = read(fd, buff, 1000000);
	buff[readed] = '\0';
	return (buff);
}

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
	// print_env(shell->envr);
	// export(shell, "x=ALO");
	// export(shell, "x=BLO");
	// unset(shell, "xxxx");
	// print_env(shell->envr);
	// printf("\n\n\n");
	// export_no_option(shell->envr);
	token_list = NULL;
	
	while (1)
	{
		cmd_line = readline("MINISHELL HOPAR:");
		if (cmd_line && *cmd_line)
		{
			tokenization(cmd_line, &token_list);
			if (syntax_validator(token_list) == 2)
				printf("EROR HAPPENED, not definied yet\n");
			expander(token_list, shell->envr);
			token_to_cmds(shell, token_list);
			printf("%d\n", shell->cmds->infile);
			printf("%d\n", shell->cmds->outfile);
			// printf("CMD:%s\nARGS: ", shell->cmds->cmd_path);
			// 	for (int i = 0; shell->cmds->cmd_args[i]; i++)
			// 		printf("'%s'",shell->cmds->cmd_args[i]);
			// printf("\nINPUT VALUE(fd=%d):'%s'\n",shell->cmds->infile,read_all(shell->cmds->infile));
			// t_cmd *cmd = shell->cmds;
			// while (cmd)
			// {
			// 	printf("CMD:%s\n", cmd->cmd_path);
			// 	for (int i = 0; cmd->cmd_args[i]; i++)
			// 		printf("ARG_%d: '%s'\n", i, cmd->cmd_args[i]);
			// 	cmd = cmd->next;
			// }
			// execve(shell->cmds->cmd_path, shell->cmds->cmd_args, env);
			if (ft_strcmp(shell->cmds->cmd_path, "pwd") == 0)
				pwd(shell->cmds->outfile);
			// close(shell->cmds->outfile);
			print_token_list(token_list);
			add_history(cmd_line);
		}
		ft_token_list_clear(&token_list);
		free(cmd_line);
	}
	rl_clear_history();
}
