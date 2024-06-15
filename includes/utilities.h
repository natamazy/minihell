/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:16:01 by aggrigor          #+#    #+#             */
/*   Updated: 2024/06/15 22:46:29 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

# include "minishell.h"
# include "tokenization.h"

t_env_elem	*init_env(char **env);
void		check_env(t_shell *shell);
char		*find_key(char *full_key_val);
char		*find_value(char *full_key_val);
char		*join(char const *s1, char const *s2);
char		*get_var_in_env(t_env_elem *envr, char *var);
char		*agvanistan(char *str, int *i, int len, t_env_elem *envr);
void		dollar_opener(t_token *token, int len, t_env_elem *envr);
void		remove_empty_fields(t_token *token, int empty_fields);

// utilities_1.c
int			ft_isalpha(int c);
int			ft_isspace(char c);
int			ft_is_operator(char *s, int i);

// utilities_2.c
void		print_token_list(t_token *token_list);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlen(const char *s);
void		ft_token_list_clear(t_token **lst);
int			ft_strcmp(char *s1, char *s2);

// utilities_3.c
int			ft_env_elem_size(t_env_elem *begin_list);
t_env_elem	*ft_env_elem_at(t_env_elem *begin_list, unsigned int nbr);
t_env_elem	*ft_merge_sorted_list(t_env_elem *left, t_env_elem *right,
			int (*cmp)());
t_env_elem	*merge_sort(t_env_elem *begin_list, int (*cmp)());
void		ft_env_elem_sort(t_env_elem **begin_list, int (*cmp)());

// utilities_4.c
char		*ft_strjoin(char const *s1, char const *s2, char sep);
int			ft_lstsize(t_env_elem *lst);
int			count_cmds(t_cmd *cmds);
char		*ft_strdup(const char *s1);
void		ft_putstr_fd(char const *s, int fd);

// utilities_5.c
char		*ft_strnstr(const char *big, const char *little, size_t len);
void		clear_cmds(t_shell *shell);
void		free_matrix(char **matrix);

// split.c
char	**ft_split(char const *s, char c);

#endif