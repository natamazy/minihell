/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:39:03 by natamazy          #+#    #+#             */
/*   Updated: 2024/05/10 11:50:13 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

typedef struct s_token	t_token;

typedef enum e_token_type
{
	WORD,
	PIPE,
	C_QUOT,
	O_QUOT,
	L_ARR,
	R_ARR,
}	t_token_type;

struct s_token
{
	char			*value;
	t_token_type	type;
	t_token			*next;
	t_token			*prev;
};

void			tokenization(char *command_line, t_token **list_of_tokens);
t_token_type	get_token_type(char *command_line, int ind);
t_token			*ft_new_token(char *value, t_token_type type);
void			ft_add_tokenlist(t_token **list_of_tokens, t_token *new_token);

#endif
