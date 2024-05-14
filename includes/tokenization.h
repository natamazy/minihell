/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:39:03 by natamazy          #+#    #+#             */
/*   Updated: 2024/05/14 16:16:09 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

typedef struct s_token	t_token;

/*
WORD
S_PIPE - |
D_PIPE - ||
S_AND - &
D_AND - &&
O_D_QUOTE - "
C_D_QUOTE - "
O_S_QUOTE - '
C_S_QUOTE - '
L_S_REDIR - <
R_S_REDIR - >
L_D_REDIR - <<
R_D_REDIR - >>
ERROR
*/
typedef enum e_token_type
{
	WORD,
	S_PIPE,
	D_PIPE,
	S_AND,
	D_AND,
	O_D_QUOTE,
	C_D_QUOTE,
	O_S_QUOTE,
	C_S_QUOTE,
	L_S_REDIR,
	R_S_REDIR,
	L_D_REDIR,
	R_D_REDIR,
	ERROR,
}	t_token_type;

struct s_token
{
	t_token_type	type;
	char			*value;
	t_token			*next;
	t_token			*prev;
};

void			tokenization(char *cmd_line, t_token **tokens_list);
void			ft_add_token_to_list(t_token **tokens_list, t_token *new_token);
t_token_type	get_token_type(char *cmd_line, int ind);
t_token			*ft_new_token(char *value);

#endif
