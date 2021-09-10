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

#include "../include/minishell.h"

static int	check_chr(char c, char *charset)
{
	if (c == '\0')
		return (0);
	while (c != *charset && *charset != '\0')
		charset++;
	if (*charset != '\0')
		return (1);
	return (0);
}

static int	get_size(char *str, char *charset)
{
	int		size;
	char	qmbt;

	size = 0;
	if (!str)
		return (size);
	while (*str)
	{
		if (!check_chr(*str, charset))
		{
			while (*str && !check_chr(*str, charset))
			{
				qmbt = *str;
				while (is_charset(qmbt, "\"'`") && *str && *str != qmbt)
					str++;
				str++;
			}
		}
		size++;
		if (*str != '\0')
			str++;
	}
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
	tmp[idx] = ft_strtrim(tmp[idx], " ");
	free(to_free);
	to_free = NULL;
	return (tmp);
}

static	char	**get_strs(char *s, char *charset, char **tmp, int idx)
{
	int		i;
	int		start;
	char	qmbt;

	i = 0;
	while (*(s + i))
	{
		if (!check_chr(*(s + i), charset))
		{
			start = i;
			while (*(s + i) && !check_chr(*(s + i), charset))
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

	if (!s)
		return (NULL);
	tmp = (char **)ft_calloc(get_size((char *)s, charset), sizeof(char *));
	if (!tmp)
		is_error(NULL, NULL, "can't allocate memory", EXIT_FAILURE);
	return (get_strs((char *)s, charset, tmp, 0));
}
