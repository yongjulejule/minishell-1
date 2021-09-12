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

int	end_by_pipe(char *one_ln, char *to_free)
{
	size_t	len;
	size_t	cnt;

	to_free = ft_strtrim(one_ln, " \t\n");
	if (!to_free)
		is_error(NULL, NULL, "can't allocate memory", EXIT_FAILURE);
	len = ft_strlen(to_free);
	cnt = 0;
	while (len > 1 && to_free[len - 1] == '|'
		&& to_free[len - cnt - 2] == '\\')
		cnt++;
	if (to_free[len - 1] == '|' && cnt % 2 == 0)
	{
		free(to_free);
		return (0);
	}
	free(to_free);
	return (1);
}

int	end_by_esc(char *one_ln)
{
	size_t	len;
	size_t	cnt;

	len = ft_strlen(one_ln);
	cnt = 0;
	while (one_ln[len - cnt - 1] == '\\')
		cnt++;
	if (cnt % 2)
		return (0);
	return (1);
}

int	skip_qmbt(char *str, int idx)
{
	char	qmbt;

	qmbt = *(str + idx);
	if (is_charset(qmbt, "\"'`"))
	{
		idx++;
		while (*(str + idx) && *(str + idx) != qmbt)
		{
			if (*(str + idx) == '\\')
			{
				idx++;
				if (*(str + idx) == qmbt)
					idx++;
			}
			else if (*(str + idx))
				idx++;
		}
	}
	return (idx);
}

int	check_end_esc(char *str, char *charset)
{
	size_t	len;
	size_t	cnt;

	len = ft_strlen(str);
	cnt = 0;
	while (len > 1 && is_charset(*(str + len - 1), charset)
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
