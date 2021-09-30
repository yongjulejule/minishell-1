/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:33:06 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/30 16:50:47 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	get_quote_len(char *str, char *charset, char ign)
{
	int	idx;
	int	cnt;

	idx = 0;
	cnt = 0;
	if (!str || !*str)
		return (0);
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

static int	update_flag(char *str, int flag)
{
	if (*(str) == '\'' && flag != 0b010)
	{
		if (!flag)
			flag = 0b100;
		else
			flag = 0;
	}
	else if (*(str) == '\"' && flag != 0b100)
	{
		if (!flag)
			flag = 0b010;
		else
			flag = 0;
	}
	return (flag);
}

int	get_wspace_len(char *str, char *charset, char ign)
{
	int	idx;
	int	cnt;
	int	flag;

	flag = 0b0000;
	idx = 0;
	cnt = 0;
	if (!str || !*str)
		return (0);
	while (flag || (!is_charset(*(str + idx), charset) && str[idx] != '\0'))
	{
		if (*(str + idx) == ign)
			idx += 2;
		else
		{
			flag = update_flag(str + idx, flag);
			idx++;
		}
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
		len = get_quote_len(&cmdset[1], "'", '\\');
		cmd->params[p_idx] = ft_substr_wo_chr(cmdset, 1, len, '\\');
	}
	else if (is_charset(cmdset[0], "\""))
	{
		len = get_quote_len(&cmdset[1], "\"", '\\');
		cmd->params[p_idx] = ft_substr_wo_chr(cmdset, 1, len, '\\');
	}
	else
	{
		len = get_wspace_len(&cmdset[0], "\t\n ", '\\');
		cmd->params[p_idx] = ft_substr_wo_chr(cmdset, 0, len, '\\');
	}
	return (len);
}
