/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:06:21 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/20 13:42:37 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "utilities.h"
#include "syntaxer.h"
#include "builtin.h"
#include "executor.h"
#include "pipex.h"

int	g_exit_status = 0;

char	*read_all(int fd)
{
	char	*buff;
	int		readed;

	if (fd == -1)
		return ("-1");
	else if (fd == 0)
		return ("NULL");
	buff = malloc(1000001);
	if (buff == NULL)
		return (NULL);
	readed = read(fd, buff, 1000000);
	buff[readed] = '\0';
	return (buff);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((unsigned char *)s + i) = c;
		i++;
	}
	return (s);
}

void	set_singals(void)
{
	set_signal(0, signal_handler_int);
	set_signal(1, signal_handler_quit);
}

void	main_helper(char *cmd_line, t_token *token_list, t_shell *shell)
{
	add_history(cmd_line);
	tokenization(cmd_line, &token_list);
	if (g_exit_status != 2)
	{
		g_exit_status = syntax_validator(token_list);
		if (g_exit_status == 2)
			ft_token_list_clear(&token_list);
		else
		{
			expander(token_list, shell->envr, &token_list);
			if (token_list)
			{
				token_to_cmds(shell, token_list);
				ft_token_list_clear(&token_list);
				run_cmds(shell);
			}
			clear_cmds(shell);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_token	*token_list;
	char	*cmd_line;
	t_shell	*shell;

	(void) argv;
	if (argc > 1)
		perror_exit(INVALID_ARG_CNT, NULL, NULL, 1);
	shell = malloc(sizeof(t_shell));
	shell->envr = init_env(env);
	shell->cmds = NULL;
	check_env(shell);
	token_list = NULL;
	cmd_line = "";
	while (cmd_line)
	{
		set_singals();
		cmd_line = readline("\e[1;34mMINISHELL HOPAR: \e[0m");
		if (cmd_line && *cmd_line)
			main_helper(cmd_line, token_list, shell);
		free(cmd_line);
		remove_here_doc_file(shell->envr);
	}
	printf("exit\n");
	//free shell NAR JAN
	rl_clear_history();
}
