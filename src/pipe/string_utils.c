/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@42student.42seoul.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:33:06 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/15 21:05:15 by jun              ###   ########.fr       */
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
		/* TODO : get redirection here...! */
		len = split_once(&cmdset[start], "\t\n ");
		cmd->params[p_idx] = ft_substr(cmdset, start, len);
		if (ft_strchr(cmd->params[p_idx], '>')
				|| ft_strchr(cmd->params[p_idx], '<'))
/*
** TODO : make lst functions like lstnewone, lstaddback...
** each node need to get rdr flag, limiter, files. 
** we can handle it as arguments of function, like follows
** lstaddback(&(cmd->rdr), lstnewone(RDR_FROM | HEREDOC, "file", "limiter")
*/
			get_rdr_info(cmd);
	}
	return (len);
}
