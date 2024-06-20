/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:27:06 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/20 12:01:42 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utilities.h"

int	ft_check_n(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (0);
	i++;
	while (arg[i])
	{
		if (arg[i] == '-')
			return (0);
		else if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo(char **args, int fdtowrite, int *is_builtin)
{
	int	newline;
	int	i;

	newline = 1;
	i = 0;
	if (args && args[i])
		i++;
	while (args && args[i] && ft_check_n(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args && args[i])
	{
		ft_putstr_fd(args[i], fdtowrite);
		i++;
		if (args[i])
			ft_putstr_fd(" ", fdtowrite);
	}
	if (newline == 1)
		write(fdtowrite, "\n", 1);
	*is_builtin = 1;
	return (0);
}
