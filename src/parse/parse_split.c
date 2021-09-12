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

static char	*skip_qmbt(char *str)
{
	char	qmbt;

	qmbt = *str;
	if (is_charset(qmbt, "\"'`"))
	{
		str++;
		while (*str && *str != qmbt)
			str++;
	}
	return (str);
}

static int	get_size(char *str, char *charset, int size)
{
	if (!str)
		return (0);
	while (*str)
	{
		while (*str && !is_charset(*str, "\"'`") && !is_charset(*str, charset))
			str++;
		str = skip_qmbt(str);
		if (is_charset(*str, charset))
		{
			size += 2;
			str++;
			while (*str && is_charset(*str, charset))
			{
				str++;
				size++;
			}
		}
		if (*str != '\0')
			str++;
	}
	if (!is_charset(*(str - 1), charset))
		size++;
	return (size);
}

static char	**alloc_mem(char **tmp, char *start_addr, int len, int idx)
{
	char	*to_free;

	tmp[idx] = (char *)ft_calloc(len, sizeof(char));
	if (!tmp[idx])
		is_error(NULL, NULL, "can't allocate memory", EXIT_FAILURE);
	ft_strlcpy(tmp[idx], start_addr, len);
	to_free = tmp[idx];
	tmp[idx] = ft_strtrim(tmp[idx], " \t\r\v\f");
	free(to_free);
	to_free = NULL;
	return (tmp);
}

static char	**get_strs(char *s, char *charset, char **tmp, int idx)
{
	int		i;
	int		start;
	char	qmbt;

	i = 0;
	while (*(s + i))
	{
		if (!is_charset(*(s + i), charset))
		{
			start = i;
			while (*(s + i) && !is_charset(*(s + i), charset))
			{
				qmbt = *(s + i);
				while (is_charset(qmbt, "\"'`")
					&& (s + ++i) && *(s + i) != qmbt);
				i++;
			}
			tmp = alloc_mem(tmp, s + start, i - start + 1, idx++);
		}
		if (*(s + i) != '\0')
			tmp = alloc_mem(tmp, s + i++, 2, idx++);
	}
	return (tmp);
}

char	**split_by_pipe_sc(char const *s, char *charset)
{
	char	**tmp;
	int		size;

	if (!s)
		return (NULL);
	size = 1;
	if (*s == '\0' || is_charset(*s, charset))
		size = 0;
	tmp = (char **)ft_calloc(get_size((char *)s, charset, size),
			sizeof(char *));
	if (!tmp)
		is_error(NULL, NULL, "can't allocate memory", EXIT_FAILURE);
	return (get_strs((char *)s, charset, tmp, 0));
}
