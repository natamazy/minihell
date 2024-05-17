/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:14:48 by aggrigor          #+#    #+#             */
/*   Updated: 2024/05/17 16:00:36 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"
#include "utilities.h"

int	ft_isalpha(int c)
{
	return (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'));
}

int	ft_is_operator(char *s, int i)
{
	int	op_len;

	if (s[i] == '|' || s[i] == '&' || s[i] == '>' || s[i] == '<')
	{
		if (s[i + 1] && s[i] == s[i + 1])
			op_len = 2;
		else
			op_len = 1;
	}
	else
		op_len = 0;
	return (op_len);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

char	*str_type(int token_type)
{
	if (token_type == 0)
		return ("WORD");
	else if (token_type == 1)
		return ("S_PIPE");
	else if (token_type == 2)
		return ("D_PIPE");
	else if (token_type == 3)
		return ("S_AND");
	else if (token_type == 4)
		return ("D_AND");
	else if (token_type == 5)
		return ("D_QUOTE");
	else if (token_type == 6)
		return ("S_QUOTE");
	else if (token_type == 7)
		return ("IN_REDIR");
	else if (token_type == 8)
		return ("OUT_REDIR");
	else if (token_type == 9)
		return ("HERE_DOC");
	else if (token_type == 10)
		return ("APPEND_REDIR");
	else if (token_type == 11)
		return ("ERROR");
	else if (token_type == 12)
		return ("NONE");
	else if (token_type == 13)
		return ("FILEIN");
	else if (token_type == 14)
		return ("LIMITER");
	else if (token_type == 15)
		return ("FILEOUT");
	else if (token_type == 16)
		return ("APPEND_FILEOUT");
	else if (token_type == 17)
		return ("OPEN_PAR");
	else if (token_type == 18)
		return ("CLOSE_PAR");
	else
		return ("\033[0;031mTOKEN_TYPE_NOT_FOUND");
}
