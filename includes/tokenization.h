/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:39:03 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/04 13:36:23 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include <unistd.h>

typedef struct s_token	t_token;

/*
WORD
S_PIPE - |
D_PIPE - ||
S_AND - &
D_AND - &&
D_QUOTE - "
S_QUOTE - '
IN_REDIR - <
OUT_REDIR - >
HERE_DOC - <<
APPEND_REDIR - >>
ERROR
NONE
*/
typedef enum e_token_type
{
	WORD,
	S_PIPE,
	D_PIPE,
	S_AND,
	D_AND,
	D_QUOTE,
	S_QUOTE,
	IN_REDIR,
	OUT_REDIR,
	HERE_DOC,
	APPEND_REDIR,
	ERROR,
	NONE,
	FILEIN,
	LIMITER,
	FILEOUT,
	APPEND_FILEOUT,
}	t_token_type;

struct s_token
{
	t_token_type	type;
	char			*value;
	t_token			*next;
	t_token			*prev;
};

t_token_type	get_token_type(char *s, int i);
t_token_type	get_token_type_util(char *s, int i);
t_token_type	get_token_type(char *cmd_line, int ind);

t_token			*ft_new_token(char *value);
t_token			*go_to_next(t_token *current_token, int need_to_del);

size_t			ft_strlen(const char *s);

void			set_tokens(t_token *tokens_list);
void			ft_token_list_clear(t_token **lst);
void			print_token_list(t_token *token_list);
void			split_by_operators(t_token **tokens_list);
void			tokenization(char *cmd_line, t_token **tokens_list);
void			split_by_spaces(char *cmd_line, t_token **tokens_list);
void			ft_add_token_to_list(t_token **tokens_list, t_token *new_token);
void			procces_one_token(t_token *cur, t_token **tl, int *is_op, int i);
void			create_and_add_to_list(t_token **token_list, char *start, int len);
void			add_new_bef(t_token **tokens_list, t_token *cur_token, char *value);

char			*str_type(int token_type);
char			*ft_substr(char const *s, unsigned int start, size_t len);

int				quote_handling(int *i, char *cmd_line, int print);

#endif
