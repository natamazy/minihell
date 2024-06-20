/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:09:26 by aggrigor          #+#    #+#             */
/*   Updated: 2024/06/20 06:26:23 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utilities.h"
#include "builtin.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;
	const char	*compare_start;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	while (i < len && big[i] != '\0')
	{
		if (big[i] == little[0])
		{
			j = 0;
			compare_start = big + i;
			while (i + j < len && big[i + j] != '\0'
				&& little[j] != '\0'
				&& big[i + j] == little[j])
				j++;
			if (little[j] == '\0')
				return ((char *)compare_start);
			i += 1;
		}
		else
			i++;
	}
	return (NULL);
}

void	clear_cmds(t_shell *shell)
{
	t_cmd	*cmd;
	t_cmd	*tmp;

	cmd = shell->cmds;
	while (cmd != NULL)
	{
		if (cmd->cmd_path != NULL && cmd->cmd_path != cmd->cmd_args[0])
			free(cmd->cmd_path);
		if (cmd->cmd_args != NULL)
			free_matrix(cmd->cmd_args);
		if (cmd->input != 0)
			close(cmd->input);
		if (cmd->output != 1)
			close(cmd->output);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
	shell->cmds = NULL;
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix && matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int	is_builtin(char *cmd_name)
{
	if (ft_strcmp(cmd_name, "cd") == 0
		|| ft_strcmp(cmd_name, "export") == 0
		|| ft_strcmp(cmd_name, "unset") == 0
		|| ft_strcmp(cmd_name, "exit") == 0)
		return (1);
	return (0);
}

void	free_list(t_env_elem *head)
{
	t_env_elem	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}
