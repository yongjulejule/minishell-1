/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 17:34:57 by ghan              #+#    #+#             */
/*   Updated: 2021/09/12 17:34:58 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	end_by_pipe(char *one_ln)
{
	size_t	len;
	size_t	cnt;

	len = ft_strlen(one_ln);
	cnt = 0;
	while (len >= cnt + 2 && one_ln[len - 1] == '|'
		&& one_ln[len - cnt - 2] == '\\')
		cnt++;
	if (one_ln[len - 1] == '|' && cnt % 2 == 0)
		return (0);
	return (1);
}

int	end_by_esc(char *one_ln)
{
	size_t	len;
	size_t	cnt;

	len = ft_strlen(one_ln);
	cnt = 0;
	while (len >= cnt + 1 && one_ln[len - cnt - 1] == '\\')
		cnt++;
	if (cnt % 2)
		return (0);
	return (1);
}

void	skip_qmbt(char *str, int *i)
{
	char	qmbt;

	qmbt = *(str + *i);
	if (is_charset(qmbt, "\"'`"))
	{
		(*i)++;
		while (*(str + *i) && *(str + *i) != qmbt)
		{
			if (*(str + *i) == '\\')
			{
				(*i)++;
				if (*(str + *i) == qmbt)
					(*i)++;
			}
			else if (*(str + *i))
				(*i)++;
		}
	}
}

int	check_end_esc(char *str, char *charset)
{
	size_t	len;
	size_t	cnt;

	len = ft_strlen(str);
	cnt = 0;
	while (len >= cnt + 2 && is_charset(*(str + len - 1), charset)
		&& *(str + len - cnt - 2) == '\\')
		cnt++;
	if (cnt % 2)
		return (1);
	return (0);
}

char	**alloc_mem(char **tmp, char *start_addr, int len, int idx)
{
	char	*to_free;

	tmp[idx] = (char *)ft_calloc(len, sizeof(char));
	if (!tmp[idx])
		is_error(NULL, NULL, "can't allocate memory", EXIT_FAILURE);
	ft_strlcpy(tmp[idx], start_addr, len);
	to_free = tmp[idx];
	tmp[idx] = ft_strtrim(tmp[idx], " \t\n");
	free(to_free);
	to_free = NULL;
	return (tmp);
}
