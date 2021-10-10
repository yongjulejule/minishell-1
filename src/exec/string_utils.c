/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:33:06 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/10 14:27:13 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	get_wspace_idx(char *str, char *charset, char ign)
{
	int	idx;

	idx = 0;
	if (!str || !*str)
		return (0);
	while (!is_charset(*(str + idx), charset) && str[idx] != '\0')
	{
		if (*(str + idx) == ign)
			idx += 2;
		else if (*(str + idx))
			idx++;
	}
	return (idx);
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
			ret[idx++] = str[start];
		else if (str[start + 1] == c)
			ret[idx++] = str[start++ + 1];
		if (str[start])
			start++;
	}
	ret[idx] = '\0';
	return (ret);
}

int	get_wspace_len(char *str, char *charset, char ign, int cnt)
{
	int	idx;
	int	flag;

	flag = 0;
	idx = 0;
	if (!str || !*str)
		return (0);
	while (!is_charset(*(str + idx), charset) && str[idx] != '\0')
	{
		if (*(str + idx) == ign)
		{
			if (is_charset(*(str + idx + 1), " \n\t"))
			{
				cnt++;
				flag += 1;
			}
			idx += 2;
		}
		else if (*(str + idx) && *(str + idx) != ign)
			idx++;
		cnt++;
	}
	if (flag)
		cnt -= flag;
	return (cnt);
}

int	make_string(char *cmdset, t_cmd *cmd, int p_idx, int len)
{
	len = get_wspace_len(&cmdset[0], "\t\n ", '\\', 0);
	cmd->params[p_idx] = ft_substr_wo_chr(cmdset, 0, len, '\\');
	return (get_wspace_idx(&cmdset[0], "\t\n ", '\\'));
}
