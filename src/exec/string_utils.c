/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:33:06 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/28 12:25:25 by yongjule         ###   ########.fr       */
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
	{
		if (*(str + idx) == ign)
		{
			idx++;
			if (*(str + idx + 1) == ign)
				str++;
		}
		if (!*(str + idx))
			break ;
		idx++;
	}
	while (!is_charset(*(str + idx), charset) && str[idx] != '\0')
	{
		if (*(str + idx) == ign)
		{
			idx++;
			if (*(str + idx + 1) == ign)
				str++;
		}
		if (!*(str + idx))
			break ;
		idx++;
	}
	return (idx);
}

static size_t	ft_strlen_wo_chr(char *str, int len, char c)
{
	size_t	cnt;

	cnt = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str != c)
			cnt++;
		else if (*(str + 1) == c)
			str++;
		str++;
	}
	return (cnt);
}

char	*ft_substr_wo_chr(char *str, unsigned int start, size_t len, char c)
{
	size_t	idx;
	size_t	size;
	char	*ret;

	size = ft_strlen_wo_chr(&str[start], len, c);
//	printf("str : %s, start : %d, len : %zu, size : %zu, ign : %c\n", str, start, len, size, c);
	if (size > len)
		return (ft_substr(str, start, len));
	idx = 0;
	ret = (char *)ft_calloc(size + 1, sizeof(char));
	while (idx < size && start <= len)
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
//		printf("in substr : %s\n", ret);
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
