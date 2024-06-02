/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:11:42 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/02 19:06:46 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAXER_H
# define SYNTAXER_H

# include "tokenization.h"

int	syntax_validator(t_token	*token_list);

#endif