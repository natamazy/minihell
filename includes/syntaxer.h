/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarapet <nkarapet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:11:42 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/19 19:14:58 by nkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAXER_H
# define SYNTAXER_H

# include "tokenization.h"
# include "minishell.h"

int		syntax_validator(t_token	*token_list);
void	expander(t_token *tokens, t_env_elem *envr, t_token **list);

#endif