/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jun <yongjule@42student.42seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 17:18:48 by jun               #+#    #+#             */
/*   Updated: 2021/09/11 15:19:43 by yongjule         ###   ########.fr       */
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
	int	len;
	int	start;

	start = 0;
	if (is_charset(cmdset[start], "'"))
	{
		len = split_once(&cmdset[start], "'");
		cmd->params[p_idx]
			= ft_substr(cmdset, start + 1, len - 1);
	}
	else if (is_charset(cmdset[start], "\""))
	{
		len = split_once(&cmdset[start], "\"");
		cmd->params[p_idx]
			= ft_substr(cmdset, start + 1, len - 1);
	}
	else
	{
		len = split_once(&cmdset[start], "\t\n\v\f\r ");
		cmd->params[p_idx] = ft_substr(cmdset, start, len);
	}
	return (len);
}
