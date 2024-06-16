/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:19:50 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/14 18:04:59 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

void	export_with_option(t_shell *shell, char *var);
void	unset(t_shell *shell, char *key_to_unset);
void	export_no_option(t_env_elem *envr);
void		print_env(t_env_elem *envr, int *is_builtin);

t_env_elem	*create_copy(t_env_elem *head);
void		create_copy_helper(t_env_elem **head, t_env_elem **current_new,
							t_env_elem **current_orig, t_env_elem **new_head);
void		export_helper_2(t_env_elem **temp, char *key, char *value);
void		export_helper_1(char **key, char **value, char *var);
void		export_with_option(t_shell *shell, char *var);
void		unset(t_shell *shell, char *key_to_unset);
void		export_no_option(t_env_elem *envr);
void		free_list(t_env_elem *head);
int			is_there_eq_sign(char *str);

char	**env_list_to_array(t_env_elem *temp);

void	pwd(int fdtowrite, int *is_builtin);

#endif