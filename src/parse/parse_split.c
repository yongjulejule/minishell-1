/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 18:13:39 by yongjule          #+#    #+#             */
/*   Updated: 2021/08/07 15:11:54 by jun              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	skip_normal_bslash(char *s, int *i)
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

static int	get_size(char *s, char *charset, int size, int i)
{
	if (!s)
		return (0);
	while (*(s + i))
	{
		skip_normal_bslash(s, &i);
		skip_qmbt(s, &i);
		if (is_charset(*(s + i), "&<>"))
			check_rdr_size(s, &size, &i);
		if (is_charset(*(s + i), charset))
		{
			size += 2;
			i++;
			while (*(s + i) && is_charset(*(s + i), charset))
			{
				i++;
				size++;
			}
		}
		else if (*(s + i) != '\0' && !is_charset(*(s + i), "\\<>&"))
			i++;
	}
	if (*s == '\0' || !is_charset(*(s + i - 1), charset)
		|| check_end_esc(s, charset))
		size++;
	return (size);
}

static void	get_end(char *s, int *i)
{
	char	qmbt;

	while (*(s + *i) && !is_charset(*(s + *i), ";|<>&"))
	{
		if (*(s + *i) != '\\')
		{
			qmbt = *(s + (*i)++);
			while (is_charset(qmbt, "\"'`")
				&& *(s + *i) && *(s + *i) != qmbt)
				(*i)++;
			if (is_charset(qmbt, "\"'`"))
				(*i)++;
		}
		else
		{
			(*i)++;
			if (is_charset(*(s + *i), "\\;|'\"`"))
				(*i)++;
		}
	}
}

static char	**get_strs(char *s, char **tmp, int idx, int i)
{
	int		start;

	while (*(s + i))
	{
		if (!is_charset(*(s + i), ";|<>&") || is_charset(*(s + i), "<>&"))
		{
			start = i;
			if (!is_charset(*(s + i), ";|<>&"))
			{
				get_end(s, &i);
				if (is_charset(*(s + i), "<>&")
					&& i > 0 && ft_isdigit(*(s + i - 1)))
					get_rdr_end_idx(s, start, &i);
			}
			else if (is_charset(*(s + i), "<>&"))
				get_rdr_end_idx(s, start, &i);
			tmp = alloc_mem(tmp, s + start, i - start + 1, idx++);
		}
		else if (*(s + i) != '\0')
			tmp = alloc_mem(tmp, s + i++, 2, idx++);
	}
	return (tmp);
}

char	**split_by_pipe_sc(char const *s, char *charset)
{
	char	**ret;
	int		size;

	if (!s)
		return (NULL);
	size = 1;
	if (is_charset(*s, ";|<>"))
		size = 0;
	ret = (char **)ft_calloc(get_size((char *)s, charset, size, 0),
			sizeof(char *));
	if (*s == '\0')
		ret = alloc_mem(ret, (char *)s, 1, 0);
	else
		ret = get_strs((char *)s, ret, 0, 0);
	return (ret);
}
