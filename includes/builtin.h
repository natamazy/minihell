/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:19:50 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/13 16:53:30 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

void	export(t_shell *shell, char *var);
void	export_no_option(t_env_elem *envr);
char	**env_list_to_array(t_env_elem *temp);
void	print_env(t_env_elem *envr);
void	unset(t_shell *shell, char *key_to_unset);

#endif