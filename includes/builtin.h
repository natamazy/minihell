/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:19:50 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/03 22:15:06 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

void	export(t_shell *shell, char *var);
void	export_no_option(t_env_elem *envr);
char	**env_list_to_array(t_env_elem *temp);

#endif