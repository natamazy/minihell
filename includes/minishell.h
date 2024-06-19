/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:44:33 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/19 23:21:35 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <termios.h>
# include <signal.h>
# include "readline/readline.h"
# include "readline/history.h"

# define TRUE 11
# define FALSE 22

# define HERE_DOC_FILE "hd_tmp_file"
# define TERM_CODE_SHIFT 128

typedef struct s_env_elem	t_env_elem;
typedef struct s_cmd		t_cmd;

typedef struct s_cmd
{
	int		input;
	int		output;
	char	*cmd_path;
	char	**cmd_args;
	t_cmd	*next;
}	t_cmd;

typedef struct s_env_elem
{
	char		*key;
	char		*value;
	t_env_elem	*next;
}	t_env_elem;

typedef struct s_shell
{
	t_env_elem	*envr;
	t_cmd		*cmds;
}	t_shell;

#endif