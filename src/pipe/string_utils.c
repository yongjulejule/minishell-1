/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@42student.42seoul.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:33:06 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/20 09:59:22 by yongjule         ###   ########.fr       */
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

	if (is_charset(cmdset[0], "'"))
	{
		len = split_once(&cmdset[0], "'");
		if (cmdset[1] == '\'')
			cmd->params[p_idx] = ft_strdup("");
		else
			cmd->params[p_idx] = ft_substr(cmdset, 1, len - 1);
	}
	else if (is_charset(cmdset[0], "\""))
	{
		len = split_once(&cmdset[0], "\"");
		if (cmdset[1] == '"')
			cmd->params[p_idx] = ft_strdup("");
		else
			cmd->params[p_idx] = ft_substr(cmdset, 1, len - 1);
	}
	else
	{
		len = split_once(&cmdset[0], "\t\n ");
		cmd->params[p_idx] = ft_substr(cmdset, 0, len);
	}
	return (len);
}
