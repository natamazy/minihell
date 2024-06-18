/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:43:03 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/18 11:07:26 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include "tokenization.h"

void	init_fds(t_fds *fds);
void	token_to_cmds(t_shell *shell, t_token *tokens);
void	token_to_cmds_helper(t_token *temp2, int *len, t_fds *fds);
void	token_to_cmds_helper1(int *len, t_token *t2, char **cm, t_token **t);

t_cmd	*ft_lstnew(char **cmd_args, t_fds *fds);
void	ft_lstadd_back(t_shell *shell, t_cmd *new);
void	here_doc_write(int tmp_file_fd, char *lim);
int		here_doc_open(char *lim);
int		open_file(char *fn, int type);

void	disable_echoctl(void);
void	signal_handler_quit(int sig);
void	ignore_sigquit(void);
void	signal_handler_int(int sig);
void	set_signal(int flag, void (*f));

#endif