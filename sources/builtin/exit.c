/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 10:52:38 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/20 13:34:39 by natamazy         ###   ########.fr       */
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
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
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

void	built_exit(t_cmd *cmd, int *is_builtin, int is_in_fork, int print)
{
	if (is_in_fork != 1)
		printf("exit\n");
	if (cmd->cmd_args[1])
	{
		if (cmd->cmd_args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			g_exit_status = 1;
			print = 1;
		}
		else if (is_numeric(cmd->cmd_args[1]))
			g_exit_status = (ft_latoi(cmd->cmd_args[1]) % 256);
		else
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd->cmd_args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			g_exit_status = 255;
		}
	}
	if (g_exit_status < 0)
		g_exit_status += 256;
	*is_builtin = 1;
	if (print != 1)
		exit(g_exit_status);
}
