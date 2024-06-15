/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:56:11 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/14 18:35:36 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utilities.h"

void	pwd(int fdtowrite)
{
	char	path[PATH_MAX];

	(void) fdtowrite;
	if (!getcwd(path, PATH_MAX))
	{
		ft_putstr_fd("ERROR\n", fdtowrite);
		return ;
	}
	ft_putstr_fd(path, fdtowrite);
	ft_putstr_fd("\n", fdtowrite);
}
