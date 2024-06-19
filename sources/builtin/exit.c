/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 10:52:38 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/19 17:03:07 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "builtin.h"
#include "minishell.h"
#include "utilities.h"

extern int	g_exit_status;

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	len_error(const char *str, unsigned long long nbr)
{
	if (nbr > (unsigned long long)LLONG_MAX + 1)
	{
		printf("minishell: exit: %s: numeric argument required\n", str);
		g_exit_status = 255;
		exit (g_exit_status);
	}
}

int	ft_latoi(const char *str)
{
	size_t				i;
	unsigned long long	nbr;
	int					sign;

	i = 0;
	nbr = 0;
	sign = 0;
	while (str[i] && ft_isspace(str[i]))
		++i;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = 1;
		++i;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nbr = (nbr * 10) + (str[i] - '0');
		if (nbr > LLONG_MAX)
			len_error(str, nbr);
		++i;
	}
	if (sign)
		return (-nbr);
	return (nbr);
}

void	built_exit(t_cmd *cmd, int *is_builtin)
{
	printf("exit\n");
	if (cmd->cmd_args[1])
	{
		if (cmd->cmd_args[2])
		{
			printf("minishell: exit: too many arguments\n");
			g_exit_status = 1;
		}
		else if (is_numeric(cmd->cmd_args[1]))
			g_exit_status = (ft_latoi(cmd->cmd_args[1]) % 256);
		else
		{
			printf("minishell: exit: %s: numeric argument required\n",
				cmd->cmd_args[1]);
			g_exit_status = 255;
		}
	}
	if (g_exit_status < 0)
		g_exit_status += 256;
	*is_builtin = 1;
}
