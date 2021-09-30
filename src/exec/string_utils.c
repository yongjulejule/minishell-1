/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:33:06 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/30 09:53:18 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	split_once(char *str, char *charset, char ign)
{
	int	idx;
	int	cnt;

	idx = 0;
	cnt = 0;
	if (!str || !*str)
		return (0);
	while (is_charset(*(str + idx), charset))
		idx++;
	while (!is_charset(*(str + idx), charset) && str[idx] != '\0')
	{
		if (*(str + idx) == ign)
		{
			idx++;
			if (*(str + idx) == ign)
				idx++;
		}
		else
			idx++;
		cnt++;
	}
	return (cnt);
}

char	*ft_substr_wo_chr(char *str, unsigned int start, size_t len, char c)
{
	size_t	idx;
	char	*ret;

	idx = 0;
	ret = (char *)ft_calloc(len + 1, sizeof(char));
	while (idx < len)
	{
		if (str[start] != c)
		{
			ret[idx] = str[start];
			idx++;
		}
		else if (str[start + 1] == c)
		{
			ret[idx] = str[start + 1];
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

	len = 2;
	if (!ft_strcmp(cmdset, "\'\'") || !ft_strcmp(cmdset, "\"\""))
		cmd->params[p_idx] = ft_strdup("");
	else if (is_charset(cmdset[0], "'"))
	{
		len = split_once(&cmdset[1], "'", '\\');
		cmd->params[p_idx] = ft_substr_wo_chr(cmdset, 1, len, '\\');
	}
	else if (is_charset(cmdset[0], "\""))
	{
		len = split_once(&cmdset[1], "\"", '\\');
		cmd->params[p_idx] = ft_substr_wo_chr(cmdset, 1, len, '\\');
	}
	else
	{
		len = split_once(&cmdset[0], "\t\n ", '\\');
		cmd->params[p_idx] = ft_substr_wo_chr(cmdset, 0, len, '\\');
	}
	return (len);
}
