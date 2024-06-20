/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:56:11 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/20 12:00:45 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utilities.h"

int	pwd(int fdtowrite, int *is_builtin)
{
	char	path[PATH_MAX];

	if (!getcwd(path, PATH_MAX))
	{
		ft_putstr_fd("minishell: can't read getcwd\n", fdtowrite);
		return (1);
	}
	ft_putstr_fd(path, fdtowrite);
	ft_putstr_fd("\n", fdtowrite);
	*is_builtin = 1;
	return (0);
}
