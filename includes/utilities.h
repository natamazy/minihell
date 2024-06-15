/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:16:01 by aggrigor          #+#    #+#             */
/*   Updated: 2024/06/15 15:21:36 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

# include "minishell.h"
# include "tokenization.h"

t_env_elem	*init_env(char **env);
size_t		ft_strlen(const char *s);
void		print_token_list(t_token *token_list);
void		ft_env_elem_sort(t_env_elem **begin_list, int (*cmp)());
void		ft_token_list_clear(t_token **lst);
void		check_env(t_shell *shell);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*find_key(char	*full_key_val);
char		*find_value(char	*full_key_val);
char		*ft_strjoin(char const *s1, char const *s2, char sep);
int			ft_isalpha(int c);
int			ft_isspace(char c);
int			ft_lstsize(t_env_elem *lst);
int			count_cmds(t_cmd *cmds);
int			ft_is_operator(char *s, int i);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strdup(const char *s1);
char		*join(char const *s1, char const *s2);
char		*get_var_in_env(t_env_elem *envr, char *var);
char		*agvanistan(char *str, int *i, int len, t_env_elem *envr);
void		dollar_opener(t_token *token, int len, t_env_elem *envr);
void		remove_empty_fields(t_token *token, int empty_fields);
void		ft_putstr_fd(char const *s, int fd);

#endif