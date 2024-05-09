/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:39:03 by natamazy          #+#    #+#             */
/*   Updated: 2024/05/09 14:48:36 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

typedef struct s_token	t_token;

typedef enum e_token_type
{
	WORD,
}	t_token_type;

struct s_token
{
	char			*value;
	t_token_type	type;
	t_token			*next;
	t_token			*prev;
};

#endif
