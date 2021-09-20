/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 17:34:57 by ghan              #+#    #+#             */
/*   Updated: 2021/09/21 01:56:03 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	skip_normal_bslash(char *s, int *i)
{
	while (*(s + *i) && !is_charset(*(s + *i), "\"'`<>&;|"))
	{
		if (*(s + *i) == '\\')
		{
			(*i)++;
			if (is_charset(*(s + *i), "\\\"`'<>&;|"))
				(*i)++;
		}
		else if (*(s + *i))
			(*i)++;
	}
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
	ft_strlcpy(tmp[idx], start_addr, len);
	to_free = tmp[idx];
	tmp[idx] = ft_strtrim(tmp[idx], " \t\n");
	free(to_free);
	to_free = NULL;
	return (tmp);
}
