/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:14:00 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/20 12:47:21 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "builtin.h"
#include "minishell.h"
#include "utilities.h"

int	ft_isalpha_ident(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (TRUE);
	return (FALSE);
}

int	ft_isdigit(int c)
{
	if (c > '0' && c < '9')
		return (TRUE);
	return (FALSE);
}

int	ft_isalphadigit(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| c == '_' || (c > '0' && c < '9'))
		return (TRUE);
	return (FALSE);
}
