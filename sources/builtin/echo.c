/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:27:06 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/19 11:42:46 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utilities.h"

void	echo(char **args, int fdtowrite, int *is_builtin)
{
	int	newline;
	int	i;

	newline = 1;
	i = 0;
	while (args && args[i])
	{
		if (i > 0)
		{
			if (ft_strcmp("-n", args[i]) == 0)
				newline = 0;
			else
				ft_putstr_fd(args[i], fdtowrite);
		}
		i++;
	}
	if (newline == 1)
		write(fdtowrite, "\n", 1);
	*is_builtin = 1;
}
