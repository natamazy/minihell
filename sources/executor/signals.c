/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 10:53:01 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/18 16:17:23 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "utilities.h"
#include "syntaxer.h"
#include "builtin.h"
#include "executor.h"
#include "pipex.h"

extern int	g_exit_status;

void	disable_echoctl(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) != 0)
		return ;
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	signal_handler_quit(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	rl_cleanup_after_signal();
}

void	ignore_sigquit(void)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	signal_handler_int(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signal(int flag, void (*f))
{
	struct sigaction	sa;

	if (flag == 0)
		ignore_sigquit();
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = f;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (flag == 0)
		sigaction(SIGINT, &sa, NULL);
	else if (flag == 1)
		sigaction(SIGQUIT, &sa, NULL);
	disable_echoctl();
}
