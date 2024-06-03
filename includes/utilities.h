/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:16:01 by aggrigor          #+#    #+#             */
/*   Updated: 2024/06/03 22:11:58 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

# include "minishell.h"
# include "tokenization.h"

int			ft_isalpha(int c);
int			ft_isspace(char c);
void		print_token_list(t_token *token_list);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlen(const char *s);
void		ft_token_list_clear(t_token **lst);
int			ft_is_operator(char *s, int i);
t_env_elem	*init_env(char **env);
void		check_env(t_shell *shell);
int			ft_strcmp(char *s1, char *s2);
char		*find_key(char	*full_key_val);
char		*find_value(char	*full_key_val);
char		*ft_strjoin(char const *s1, char const *s2, char sep);
void		ft_env_elem_sort(t_env_elem **begin_list, int (*cmp)());
int			ft_lstsize(t_env_elem *lst);

#endif