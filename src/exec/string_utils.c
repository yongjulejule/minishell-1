/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:33:06 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/09 13:24:51 by ghan             ###   ########.fr       */
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

int	get_wspace_len(char *str, char *charset, char ign)
{
	int	idx;
	int	cnt;
	int	flag;

	flag = 0;
	idx = 0;
	cnt = 0;
	if (!str || !*str)
		return (0);
	while (!is_charset(*(str + idx), charset) && str[idx] != '\0')
	{
		if (*(str + idx) == ign)
		{
			idx += 2;
			cnt++;
			flag = 1;
		}
		else if (*(str + idx) && *(str + idx) != '\\')
			idx++;
		cnt++;
	}
	if (flag == 1)
		cnt--;
	return (cnt);
}

int	make_string(char *cmdset, t_cmd *cmd, int p_idx, int len)
{
	len = get_wspace_len(&cmdset[0], "\t\n ", '\\');
	cmd->params[p_idx] = ft_substr_wo_chr(cmdset, 0, len, '\\');
	return (len);
}
