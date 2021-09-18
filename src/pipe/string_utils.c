/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@42student.42seoul.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:33:06 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/18 20:26:25 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	split_once(char *str, char *charset)
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
		idx++;
	return (idx);
}

int	make_string(char *cmdset, t_cmd *cmd, int p_idx)
{
	int		len;
	int		start;

	start = 0;
	if (is_charset(cmdset[start], "'"))
	{
		len = split_once(&cmdset[start], "'");
		cmd->params[p_idx] = ft_substr(cmdset, start + 1, len - 1);
	}
	else if (is_charset(cmdset[start], "\""))
	{
		len = split_once(&cmdset[start], "\"");
		cmd->params[p_idx] = ft_substr(cmdset, start + 1, len - 1);
	}
	else
	{
		len = split_once(&cmdset[start], "\t\n ");
		cmd->params[p_idx] = ft_substr(cmdset, start, len);
	}
	return (len);
}
