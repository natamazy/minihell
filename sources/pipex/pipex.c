/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:09:25 by aggrigor          #+#    #+#             */
/*   Updated: 2024/06/15 22:26:31 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "minishell.h"
#include "utilities.h"

void	init_pipex(t_shell *shell, t_pipex *pipex)
{
	pipex->pipes = NULL;
	pipex->cmd_cnt = count_cmds(shell->cmds);
	pipex->cmds = shell->cmds;
	pipex->envp = shell->envr;
}

int	run_cmds(t_shell *shell)
{
	t_pipex	pipex;

	init_pipex(shell, &pipex);
	init_pipes(&pipex);
	create_processes(&pipex);
	close_pipes(&pipex);
	wait_processes(&pipex);
	if (pipex.pipes != NULL)
		free(pipex.pipes);
	pipex.pipes = NULL;
	return (EXIT_SUCCESS);
}
