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

static void	skip_normal_bslash(char *s, char *charset, int *i)
{
	while (*(s + *i) && !is_charset(*(s + *i), "\"'`")
		&& !is_charset(*(s + *i), charset))
	{
		if (*(s + *i) == '\\')
		{
			(*i)++;
			if (is_charset(*(s + *i), "\\\"`';|"))
				(*i)++;
		}
		else if (*(s + *i))
			(*i)++;
	}
}

static int	get_size(char *s, char *charset, int size)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (*(s + i))
	{
		skip_normal_bslash(s, charset, &i);
		skip_qmbt(s, &i);
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
		else if (*(s + i) != '\0' && *(s + i) != '\\')
			i++;
	}
	if (!is_charset(*(s + i - 1), charset) || check_end_esc(s, charset))
		size++;
	return (size);
}

static void	get_end(char *s, char *charset, int *i)
{
	char	qmbt;

	while (*(s + *i) && !is_charset(*(s + *i), charset))
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

static char	**get_strs(char *s, char *charset, char **tmp, int idx)
{
	int		i;
	int		start;

	i = 0;
	while (*(s + i))
	{
		if (!is_charset(*(s + i), charset))
		{
			start = i;
			get_end(s, charset, &i);
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
	if (*s == '\0' || is_charset(*s, charset))
		size = 0;
	ret = (char **)ft_calloc(get_size((char *)s, charset, size),
			sizeof(char *));
	ret = get_strs((char *)s, charset, ret, 0);
	return (ret);
}
