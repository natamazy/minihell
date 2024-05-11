/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:16:01 by aggrigor          #+#    #+#             */
/*   Updated: 2024/05/11 17:09:44 by natamazy         ###   ########.fr       */
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

#endif