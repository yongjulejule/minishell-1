/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 17:34:57 by ghan              #+#    #+#             */
/*   Updated: 2021/09/27 13:25:05 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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

static void	get_end_not_bs(char *s, int *i)
{
	char	qmbt;

	qmbt = *(s + (*i)++);
	while (is_charset(qmbt, "\"'`")
		&& *(s + *i) && *(s + *i) != qmbt)
	{
		if (*(s + *i) == '\\')
			(*i)++;
		(*i)++;
	}
	if (*(s + *i) && is_charset(qmbt, "\"'`"))
		(*i)++;
}

void	get_end_idx(char *s, int *i, char *charset, int flag)
{
	int		k;

	while (*(s + *i) && !is_charset(*(s + *i), charset))
	{
		k = 0;
		if (flag && rdr_after_fd(s + *i, &k))
			break ;
		if (*(s + *i) != '\\')
			get_end_not_bs(s, i);
		else
		{
			(*i)++;
			if (is_charset(*(s + *i), "\\;|'\"`<>&"))
				(*i)++;
		}
	}
}

int	rdr_after_fd(char *s, int *i)
{
	while (ft_isdigit(*(s + *i)))
		(*i)++;
	if (check_valid_rdr_symbols(s, *i))
		return (1);
	return (0);
}

int	check_front_whitespace(char *str, int len)
{
	int	i;

	i = 0;
	while (i < len && str && *(str + i))
	{
		if (!is_charset(*(str + i), " \n\t"))
			return (1);
		i++;
	}
	return (0);
}
