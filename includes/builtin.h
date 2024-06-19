/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:19:50 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/19 19:14:25 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "pipex.h"

int			export_with_option(t_pipex *pipex, char *var);
int			unset(t_pipex *pipex, t_cmd *cmd, int *is_builtin);
int			export_no_option(t_env_elem *envr);
int			print_env(t_env_elem *envr, int *is_builtin);

t_env_elem	*create_copy(t_env_elem *head);
void		create_copy_helper(t_env_elem **head, t_env_elem **current_new,
				t_env_elem **current_orig, t_env_elem **new_head);
void		export_helper_2(t_env_elem **temp, char *key,
				char *value, int flag);
void		export_helper_1(char **key, char **value, char *var);
int			export(t_pipex *pipex, t_cmd *cmd, int *is_builtin);
int			is_there_eq_sign(char *str);

char		**env_list_to_array(t_env_elem *temp);

int			pwd(int fdtowrite, int *is_builtin);

int			cd(char *path, t_pipex *pipex, int *is_builtin);

int			is_numeric(const char *str);
void		len_error(const char *str, unsigned long long nbr);
int			ft_latoi(const char *str);
void		built_exit(t_cmd *cmd, int *is_builtin);
int			echo(char **args, int fdtowrite, int *is_builtin);

#endif