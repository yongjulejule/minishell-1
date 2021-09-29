/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:33:06 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/29 10:35:48 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	split_once(char *str, char *charset, char ign)
{
	int	idx;

	idx = 0;
	if (!str)
		return (0);
	if (!*str)
		return (0);
	while (is_charset(*(str + idx), charset))
		idx++;
	while (!is_charset(*(str + idx), charset) && str[idx] != '\0')
	{
		if (*(str + idx) == ign)
		{
			idx++;
			if (*(str + idx) == ign || is_charset(*(str + idx), charset))
				idx++;
		}
		else
			idx++;
		if (!*(str + idx))
			break ;
	}
	return (idx);
}

static size_t	ft_strlen_wo_chr(char *str, size_t len, char c)
{
	size_t	cnt;
	size_t	idx;

	cnt = 0;
	idx = 0;
	if (!str)
		return (0);
	while (idx <= len)
	{
		if (*(str + idx) != c)
			cnt++;
		else if (*(str + idx + 1) == c)
		{
			cnt++;
			idx++;
		}
		idx++;
	}
	return (cnt);
}

char	*ft_substr_wo_chr(char *str, unsigned int start, size_t len, char c)
{
	size_t	idx;
	size_t	size;
	char	*ret;

	size = ft_strlen_wo_chr(&str[start], len, c);
	if (size > len)
		return (ft_substr(str, start, len));
	idx = 0;
	ret = (char *)ft_calloc(size + 1, sizeof(char));
	while (idx < size)
	{
		if (str[start] != c)
		{
			ret[idx] = str[start];
			idx++;
		}
		else if (str[start + 1] == c)
		{
			ret[idx] = str[start];
			idx++;
			start++;
		}
		start++;
	}
	ret[idx] = '\0';
	return (ret);
}

int	make_string(char *cmdset, t_cmd *cmd, int p_idx)
{
	int		len;

	if (!ft_strcmp(cmdset, "\'\'") || !ft_strcmp(cmdset, "\"\""))
	{
		cmd->params[p_idx] = ft_strdup("");
		len = 2;
	}
	else if (is_charset(cmdset[0], "'"))
	{
		len = split_once(&cmdset[1], "'", '\\');
		cmd->params[p_idx] = ft_substr_wo_chr(cmdset, 1, len - 1, '\\');
	}
	else if (is_charset(cmdset[0], "\""))
	{
		len = split_once(&cmdset[1], "\"", '\\');
		cmd->params[p_idx] = ft_substr_wo_chr(cmdset, 1, len - 1, '\\');
	}
	else
	{
		len = split_once(&cmdset[0], "\t\n ", '\\');
		cmd->params[p_idx] = ft_substr_wo_chr(cmdset, 0, len, '\\');
	}
	return (len);
}
