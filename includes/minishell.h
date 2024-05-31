/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:44:33 by natamazy          #+#    #+#             */
/*   Updated: 2024/05/28 14:52:49 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "readline/readline.h"
# include "readline/history.h"

typedef struct s_env_elem	t_env_elem;

typedef struct s_env_elem
{
	char		*key;
	char		*value;
	t_env_elem	*next;
}	t_env_elem;

typedef struct s_shell
{
	t_env_elem	*envr;
}	t_shell;

#endif