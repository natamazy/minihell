/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:39:03 by natamazy          #+#    #+#             */
/*   Updated: 2024/05/12 18:11:55 by aggrigor         ###   ########.fr       */
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

enum e_quote
{
	OPENED,
	CLOSED
};
void			tokenization(char *command_line, t_token **list_of_tokens);
void			ft_add_token_to_list(t_token **list_of_tokens, t_token *new_token);
t_token_type	get_token_type(char *command_line, int ind);
t_token			*ft_new_token(char *value);

#endif
