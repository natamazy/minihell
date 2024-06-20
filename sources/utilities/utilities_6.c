/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:48:12 by aggrigor          #+#    #+#             */
/*   Updated: 2024/06/20 17:39:11 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "utilities.h"
#include "pipex.h"

void	remove_here_doc_file(t_env_elem *envr)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror_exit(FORK_ERR, NULL, NULL, 1);
	if (pid == 0)
	{
		if (execve("/bin/rm", (char *[4]){RM, RF, HERE_DOC_FILE, NULL},
			env_list_to_array(envr)) == -1)
			perror_exit(EXECVE_ERR, NULL, NULL, 1);
	}
}

size_t	count_num_len(long long int k)
{
	size_t		num_len;

	num_len = 0;
	if (k == 0)
		num_len++;
	else if (k < 0)
	{
		num_len++;
		k *= -1;
	}
	while (k != 0)
	{
		num_len++;
		k /= 10;
	}
	return (num_len);
}

void	int_to_str(long long int k, size_t num_len, char *str_num)
{
	size_t			i;

	if (k == 0)
		str_num[0] = '0';
	else if (k < 0)
	{
		str_num[0] = '-';
		k *= -1;
	}
	i = 1;
	while (k != 0)
	{
		str_num[num_len - i] = '0' + (k % 10);
		k /= 10;
		i++;
	}
	str_num[num_len] = '\0';
}

char	*ft_itoa(int n)
{
	char			*str_num;
	size_t			num_len;

	num_len = count_num_len((long long int) n);
	str_num = (char *)malloc((num_len + 1) * sizeof(char));
	if (str_num == NULL)
		return (NULL);
	int_to_str((long long int) n, num_len, str_num);
	return (str_num);
}

int	global(int exit_status, int set)
{
	static int	status;

	if (set == 1)
		status = exit_status;
	return (status);
}
